#pragma once

#include "../../skxx/core/sk_common.hxx"

class SK_NativeAction_test : public SK::SK_NativeAction_Root {
public:
    SK_NativeAction_test() {
        run = [&](const nlohmann::json& payload, SK::SK_Communication_Response& respondWith) {
            //perform some action
            //...your code here

            //then respond
            respondWith.JSON({{"hello", "world"}});
        };
    };
};
