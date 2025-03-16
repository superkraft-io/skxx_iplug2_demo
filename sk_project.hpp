#pragma once

#include "skxx/core/sk_common.hpp"
#include "skxx/core/superkraft.hpp"

#include "IPlugPlatform.h"

#if defined(SK_APP_TYPE_app)
    #include "IPlugAPP_host.h"
    using iPlugInstance = IPlugAPP;
#elif defined(SK_APP_TYPE_au2)
    //#include "IPlugAU.h"
    using iPlugInstance = iplug::IPlugAPIBase;
#endif




using namespace iplug;

class SK_Project {
public:
    static inline bool initialized;
    static inline bool onSoftBackend_isReady_executed;
    
    static inline iPlugInstance* instance;
    
    static inline void init(iPlugInstance* _instance){
        if (initialized) return;
        
        instance = _instance;
        
        SK::SK_Machine::cpuInfo = SK::SK_Machine::getCPUInformation();
        Superkraft::_sk = new Superkraft();
        
        SK_Global::getMainWindowSize = [&]() {
          SK_Point size{instance->GetEditorWidth(), instance->GetEditorHeight()};
          return size;
        };

        SK_Global::setMainWindowSize = [&](int w, int h) {
        instance->SetEditorSize(w, h);
        instance->OnParentWindowResize(w, h);


          SK_Global::resizeAllMainWindowView(0, 0, w, h, 1);

          #if defined(SK_OS_windows)
            float scale = getHWNDScale(SK_Global::mainWindow->wndHandle);
            SetWindowPos(SK_Global::mainWindow->wndHandle, NULL, 0, 0, w * scale, h * scale, SWP_NOMOVE | SWP_NOZORDER);
            SendMessage(SK_Global::mainWindow->wndHandle, WM_SIZE, SIZE_RESTORED, MAKELPARAM(w * scale, h * scale));
          #endif
        };


        SK_Global::onMainWindowHWNDAcquired = [&](void* handle) {
            SK_Window* wnd = Superkraft::sk()->wndMngr.newWindow([&](SK_Window* wnd) {
                SK_Global::mainWindow = wnd;

                wnd->config.data["width"] = instance->GetEditorWidth();
                wnd->config.data["height"] = instance->GetEditorHeight();

                wnd->tag = "sb";
                wnd->config["visible"] = true;
                  
                #if defined(SK_OS_windows)
                    wnd->wndHandle = static_cast<HWND>(handle);
                    SK_Global::updateWebViewHWNDListForView(wnd->windowClassName);
                #elif defined(SK_OS_apple)
                    #ifdef __OBJC__
                        wnd->wndHandle = (__bridge NSWindow*) handle;
                    #endif
                #endif
                  
                SK_Global::sb_ipc = &wnd->ipc;

                Superkraft::sk()->comm.sb_ipc = &wnd->ipc;

                SK_Project::onSoftBackend_isReady();
            });
        };

          
          
          
          

        SK_Global::onWebViewReady = [&](void* webview, bool isHardBackend) {
            Superkraft::sk()->wvinit.init(webview, isHardBackend);
        };

        SK_IPC_v2::onSendToFrontend = [&](const SK_String& target, const SK_String& data) {
            SK_String str = "sk_api.ipc.handleIncoming(" + data + ")";

            if (target == "sk:sb") {
                instance->EvaluateJavaScript(str.c_str());
            }
            else {
                SK_Window* view = Superkraft::sk()->wndMngr.findWindowByTag(target);
                view->webview.evaluateScript(str, NULL);
            }
        };
    }
    
    static inline void onSoftBackend_isReady(){
        if (onSoftBackend_isReady_executed) return;
        
        SK_Global::sb_ipc->on("sk_app_is_ready", [](nlohmann::json data, SK_Communication_Packet* packet) {
            packet->response()->JSON_OK();
            SK_App_Initializer::emitAppEvent("ready", {});
        });
        
        
        
        SK_Global::sb_ipc->on("valid_event_id", [](nlohmann::json data, SK_Communication_Packet* packet) {
            nlohmann::json json;

            std::string frontend_message = std::string(data["key"]);

            json["backend_said"] = "hello frontend :)";
            packet->response()->JSON(json);
        });

        SK_Global::sb_ipc->once("valid_event_id_once", [](nlohmann::json data, SK_Communication_Packet* packet) {
            nlohmann::json json;

            SK_String frontend_message = data["key"];

            json["backend_said"] = "hello frontend :) deleting this event now";
            packet->response()->JSON(json);
        });


        SK_Global::sb_ipc->onMessage = [&](const SK_String& sender, SK_Communication_Packet* packet) {
            SK_String action = packet->data["action"];

            if (action == "reqFromBE") {
                nlohmann::json be_data;
                be_data["this_is"] = "a backend request :)";
                
                SK_Global::sb_ipc->request("sk:hb", "sk:sb", "requestFromBackend", be_data, [](const SK_String& sender, SK_Communication_Packet* packet) {
                    SK_String key = packet->data["key"];
                    DBGMSG("key = %s\n", key.c_str());
                });
            }
            else if (action == "msgFromBE")
            {
                nlohmann::json be_data;
                be_data["this_is"] = "a message from backend :)";

                SK_Global::sb_ipc->message(be_data);
            }
            else {
                DBGMSG("data = %s\n", packet->data.dump().c_str());
            }
        };
    }
};
