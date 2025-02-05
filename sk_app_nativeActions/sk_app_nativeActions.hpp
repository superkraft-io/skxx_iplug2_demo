#pragma once


#include "../skxx/core/sk_common.hpp"

#include "test/test.hpp"

class SK_App_NativeActions {
public:

    std::unordered_map<std::string, void*> actions {
        {"test", new SK_NativeAction_test()}
    };

    ~SK_App_NativeActions() {
        for (auto& pair : actions) {
            delete pair.second;
        }
        actions.clear();
    }
    

    bool handleOperation(const SK::SK_String& operation, const nlohmann::json& payload, SK::SK_Communication_Response& respondWith) {
        void* action = actions[operation];

        if (!action) return false;

        static_cast<SK::SK_NativeAction_Root*>(action)->run(payload, respondWith);

        return true;
    };
};
