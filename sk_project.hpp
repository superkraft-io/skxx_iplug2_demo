#pragma once

#include "skxx/core/sk_common.hpp"
#include "skxx/core/superkraft.hpp"

#include "IPlugWebUI_SK.h"

#include "IPlugPlatform.h"


using namespace iplug;

class SK_Project {
public:
    SK_Global* skg;

    bool initialized = false;
    bool onSoftBackend_isReady_executed = false;
    
    IPlugAPIBase* instance;
    
    SK_Project(SK_Global* _skg) {
        skg = _skg;
    }

    void init(IPlugAPIBase* _instance = nullptr){
        if (initialized) return;

        if (_instance) {
            instance = _instance;
        }

        skg->getPluginInstance = [&]() {
            return instance;
        };
        
        skg->findPluginParamByName = [&](const std::string& paramName) -> iplug::IParam* {
            for (int i = 0; i < kNumParams; i++) {
                IParam* param = instance->GetParam(i);
                if (SK_String(param->GetName()) == paramName) {
                    return param;
                }
            }
            
            return nullptr;
        };
        
        skg->findPluginParamIdxByName = [&](const std::string& paramName) {
            IParam*  targetParam = skg->findPluginParamByName(paramName);
            
            for (int i = 0; i < kNumParams; i++) {
               if (instance->GetParam(i) == targetParam){
                   return i;
               }
            }
            
            return -1; // Not found
        };
        
        SK_Machine* skm = static_cast<SK_Machine*>(skg->machine);
        skm->cpuInfo = skm->getCPUInformation();

        skg->sendMsgToWebview = [&](const SK_String& target, const SK_String& data) {
            SK_String str = "sk_api.ipc.handleIncoming(" + data + ")";

            if (target == "sk:sb") {
                instance->EvaluateJavaScript(str.c_str());
            }
            else {
                SK_Window* view = static_cast<Superkraft*>(skg->sk)->wndMngr->findWindowByTag(target);
                if (view) view->webview.evaluateScript(str, NULL);
            }
         };

        
        
        skg->handlePluginParamEvent = [&](const nlohmann::json& payload, SK_Communication_Response& respondWith){
            SK_String pluginParamID = payload["pluginParamID"];
            iplug::IParam* param = skg->findPluginParamByName(pluginParamID);
            int paramIdx = skg->findPluginParamIdxByName(pluginParamID);

            if (param == NULL) {
                respondWith.error(404, "invalid_plugin_param_id");
                return;
            }

            SK_String event = payload["event"];

            if (event == "contextmenu") {
                if (skg->runningAs == "app") {
                    respondWith.error(404, "standalone_runtime");
                    return;
                }

                int left = payload["left"];
                int top = payload["top"];

                #if defined(SK_FRAMEWORK_JUCE)
                    auto ctx = vbe->editor->getHostContext();
                    std::unique_ptr<juce::HostProvidedContextMenu> menu = ctx->getContextMenuForParameter(param);
                    menu.get()->showNativeMenu(Points<int>{left, top});
                #elif defined(SK_FRAMEWORK_iPlug2)
                    //WHY IS THIS NOT ACTIVATED???
                    //wip
                    int x = 0;
                #endif
            }
            else if (event == "read") {
                respondWith.JSON(nlohmann::json{
                    {"value", param->Value()}
                });
                
                return;
            }
            else if (event == "write") {
                float value = payload["value"];
                //double normalizedValue = param->ToNormalized(value);
                param->Set(value);
            }
            else if (event == "mousedown"){
                instance->BeginInformHostOfParamChangeFromUI(paramIdx);
            }
            else if (event == "mouseup"){
                instance->EndInformHostOfParamChangeFromUI(paramIdx);
            }
                                             
            respondWith.JSON_OK();
        };
        
        
        
        
        
        
        
        skg->getMainWindowSize = [&]() {
            SK_Point size{instance->GetEditorWidth(), instance->GetEditorHeight()};
            return size;
        };

        skg->setMainWindowSize = [&](int w, int h) {
            instance->SetEditorSize(w, h);
            instance->OnParentWindowResize(w, h);


            skg->resizeAllMainWindowViews(0, 0, w, h, 1);

            #if defined(SK_OS_windows)
                float scale = skg->mainWindow->getHWNDScale(skg->mainWindow->wndHandle);
                SetWindowPos(skg->mainWindow->wndHandle, NULL, 0, 0, w * scale, h * scale, SWP_NOMOVE | SWP_NOZORDER);
                SendMessage(skg->mainWindow->wndHandle, WM_SIZE, SIZE_RESTORED, MAKELPARAM(w * scale, h * scale));
            #endif
        };


        skg->onMainWindowHWNDAcquired = [&](void* handle, bool isView = false) {
            SK_Window* wnd = static_cast<Superkraft*>(skg->sk)->wndMngr->newWindow([&](SK_Window* wnd) {
                skg->mainWindow = wnd;

                wnd->config.data["width"] = instance->GetEditorWidth();
                wnd->config.data["height"] = instance->GetEditorHeight();

                wnd->tag = "sb";
                wnd->config["visible"] = true;
                  
                #if defined(SK_OS_windows)
                    wnd->wndHandle = static_cast<HWND>(handle);
                    skg->updateWebViewHWNDListForView(wnd->windowClassName);
                #elif defined(SK_OS_apple)
                    #ifdef __OBJC__
                        if (!isView){
                            wnd->wndHandle = (__bridge NSWindow*) handle;
                            wnd->contentView = wnd->wndHandle.contentView;
                        } else {
                            wnd->contentView = (__bridge NSView*) handle;
                            wnd->wndHandle = wnd->contentView.window;
                        }
                    #endif
                #endif
                  
                skg->sb_ipc = wnd->ipc;
                
                wnd->onDestroyed = [&, wnd](){
                    #if defined(SK_OS_apple)
                        SK_Window_MacOS_Delegate* wndDelegate = wnd->wndDelegate;
                    #endif
                    
                    skg->sb_ipc = nullptr;
                };

                static_cast<Superkraft*>(skg->sk)->comm->sb_ipc = wnd->ipc;

                onSoftBackend_isReady();
            });
        };

          
          
          
          

        skg->onWebViewReady = [&](void* webview, bool isHardBackend) {
            static_cast<Superkraft*>(skg->sk)->wvinit.init(webview, isHardBackend);
        };


        
        
        skg->onPreConfigWnd = [](SK_Window* wnd, nlohmann::json constructorOpts){
           //code here
        };

        #if defined(SK_APP_TYPE_plugin)
            skg->onPostConfigWnd = [](SK_Window* wnd) {
                for (auto& [key, value] : wnd->config_updateTracker.items()) {
                    value = false;
                }
            };

            skg->onWndCreated = [](SK_Window* wnd) {
                wnd->updateWebView();
            };
        #endif
    }
    
    void onSoftBackend_isReady(){
        if (onSoftBackend_isReady_executed) return;

        SK_IPC_v2* ipc = static_cast<SK_IPC_v2*>(skg->sb_ipc);

        SK_Global* _skg = skg;
        ipc->on("sk_app_is_ready", [&, _skg](nlohmann::json data, SK_Communication_Packet* packet) {
            packet->response()->JSON_OK();

            SK_App_Initializer* appInitializer = static_cast<SK_App_Initializer*>(skg->appInitializer);
            appInitializer->emitAppEvent("ready", {});
        });
        
        
        
        ipc->on("valid_event_id", [](nlohmann::json data, SK_Communication_Packet* packet) {
            nlohmann::json json;

            std::string frontend_message = std::string(data["key"]);

            json["backend_said"] = "hello frontend :)";
            packet->response()->JSON(json);
        });

        ipc->once("valid_event_id_once", [](nlohmann::json data, SK_Communication_Packet* packet) {
            nlohmann::json json;

            SK_String frontend_message = data["key"];

            json["backend_said"] = "hello frontend :) deleting this event now";
            packet->response()->JSON(json);
        });


        ipc->onMessage = [&](const SK_String& sender, SK_Communication_Packet* packet) {
            SK_String action = packet->data["action"];

            if (action == "reqFromBE") {
                nlohmann::json be_data;
                be_data["this_is"] = "a backend request :)";
                
                ipc->request("sk:hb", "sk:sb", "requestFromBackend", be_data, [](const SK_String& sender, SK_Communication_Packet* packet) {
                    SK_String key = packet->data["key"];
                    DBGMSG("key = %s\n", key.c_str());
                });
            }
            else if (action == "msgFromBE")
            {
                nlohmann::json be_data;
                be_data["this_is"] = "a message from backend :)";

                ipc->message(be_data);
            }
            else {
                DBGMSG("data = %s\n", packet->data.dump().c_str());
            }
        };
    }
};
