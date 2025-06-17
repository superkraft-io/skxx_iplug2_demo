#pragma once


#include "../skxx/core/sk_include.h"
#include "../skxx/core/utils/sk_string.h"
#include "../skxx/core/sk_communication/sk_communication_response.hpp"
#include "../skxx/module_system/cpp/modules/sk/nativeActions/sk_nativeAction_root.hpp"

#include "test/test.hpp"

BEGIN_SK_NAMESPACE

class SK_App_NativeActions {
public:
    SK_Global* skg;



    std::unordered_map<std::string, void*> actions {
        {"test", new SK_NativeAction_test()}
    };



    SK_App_NativeActions(SK_Global* _skg) {
        skg = _skg;
        
        for (auto& pair : actions) {
            static_cast<SK_NativeAction_Root*>(pair.second)->skg = skg;
        }
    }

    ~SK_App_NativeActions() {
        for (auto& pair : actions) {
            delete pair.second;
        }
        actions.clear();
    }
    

    bool handleOperation(const SK::SK_String& operation, nlohmann::json& payload, SK::SK_Communication_Response& respondWith) {
        void* action = actions[operation];

        if (!action) return false;

        static_cast<SK::SK_NativeAction_Root*>(action)->run(payload, respondWith);

        return true;
    };
};

END_SK_NAMESPACE
