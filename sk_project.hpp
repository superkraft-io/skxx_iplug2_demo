#pragma once

#include "skxx/core/sk_common.hpp"
#include "skxx/core/superkraft.hpp"
#include "sk_plugin_contextMenu.hpp"

#include "IPlugWebUI_SK.h"

#include "IPlugPlatform.h"

#include "WebView2.h"

using namespace iplug;

class SK_Project {
public:
    SK_Global* skg;

    bool initialized = false;
    bool onSoftBackend_isReady_executed = false;
    
    IPlugAPIBase* instance;

    SK_Plugin_ContextMenu* plugCtxMenu;

    std::vector<float> paramValues;

    #if defined(SK_OS_windows)
        //...
    #endif
    

    SK_Window* parameterListener = NULL;
    
    SK_Project(SK_Global* _skg) {
        skg = _skg;
        plugCtxMenu = new SK_Plugin_ContextMenu(skg);
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
            for (int i = 0; i < instance->NParams(); i++) {
                IParam* param = instance->GetParam(i);
                if (SK_String(param->GetName()) == paramName) {
                    return param;
                }
            }
            
            return nullptr;
        };
        
        skg->findPluginParamIdxByName = [&](const std::string& paramName) {
            IParam*  targetParam = skg->findPluginParamByName(paramName);
            
            for (int i = 0; i < instance->NParams(); i++) {
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

                plugCtxMenu->popup(paramIdx, left, top);

            }
            else if (event == "read") {
                respondWith.JSON(nlohmann::json{
                    {"value", param->Value()}
                });
                
                return;
            }
            else if (event == "write") {
                float value = payload["value"];
                double normalizedValue = param->ToNormalized(value);

                instance->SendParameterValueFromUI(paramIdx, normalizedValue);
                //instance->SetParameterValue(paramIdx, normalizedValue); //this is for VST3

                //The two lines below are for AU if the above line doesn't work for AU
                //param->SetNormalized(normalizedValue);
                //instance->EndInformHostOfParamChangeFromUI(paramIdx);
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

          
          
          
          

        skg->onWebViewReady = [&](void* wnd, void* webview, bool isHardBackend) {
            //generate ordered list of parameter names
            SK_String pluginParameters = "";
            if (instance->NParams() == 1){
                pluginParameters = "'" + SK_String(instance->GetParam(0)->GetName()) + "'";
            }
            else {
                for (int i = 0; i < instance->NParams() - 1; i++) {
                    IParam* param = instance->GetParam(i);
                    pluginParameters += "{id:'" + SK_String(param->GetName()) + "',value:" + SK_String(param->Value()) + "},";
                }

                IParam* param = instance->GetParam(instance->NParams() - 1);
                pluginParameters += "{id:'" + SK_String(param->GetName()) + "',value:" + SK_String(param->Value()) + "}";
            }

            pluginParameters = "[" + pluginParameters + "]";

            static_cast<Superkraft*>(skg->sk)->wvinit.pluginParameters = pluginParameters;




            //initialize the webview
            static_cast<Superkraft*>(skg->sk)->wvinit.init(webview, isHardBackend);

            SK_Window* _wnd = static_cast<SK_Window*>(wnd);
            if (_wnd->config.data.contains("accessPluginParameters") && _wnd->config.data["accessPluginParameters"] == true) {
                for (int i = 0; i < instance->NParams(); i++) {
                    IParam* param = instance->GetParam(i);
                    paramValues.push_back(param->Value());
                }


                parameterListener = _wnd;
            }
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
    


    void updateParamValues() {
        if (!parameterListener) return;
        
        bool anyParamHasChanged = false;

        for (int i = 0; i < instance->NParams() - 1; i++) {
            IParam* param = instance->GetParam(i);
            float value = param->Value();
            if (paramValues[i] != value) {
                paramValues[i] = value;
                anyParamHasChanged = true;
            }
        }

        if (!anyParamHasChanged) return;


        UINT bufferSize = static_cast<UINT>(paramValues.size() * sizeof(float));
        wil::com_ptr<ICoreWebView2SharedBuffer> sharedBuffer;
        HRESULT hr = parameterListener->webview.environment12->CreateSharedBuffer(bufferSize, &sharedBuffer);
        if (FAILED(hr)) {
            return;
        }        

        BYTE* bufferData = nullptr;
        hr = sharedBuffer->get_Buffer(&bufferData);
        if (FAILED(hr)) {
            return;
        }

        memcpy(bufferData, paramValues.data(), bufferSize);



        std::wstring additionalData = L"{\"id\":\"pluginParamUpdate\"}";
        hr = parameterListener->webview.webview17->PostSharedBufferToScript(
            sharedBuffer.get(),
            COREWEBVIEW2_SHARED_BUFFER_ACCESS_READ_ONLY,
            additionalData.c_str()
        );
        if (FAILED(hr)) {
            return;
        }
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
