#pragma once

#include "IPlugSWELL.h"

#if __has_include("./iPlug2_SK/IPlug/IPlugConstants.h")
    #include "config.h"
    #undef SK_FRAMEWORK_Superkraft
    #define SK_FRAMEWORK "iPlug2"
    #define SK_FRAMEWORK_iPlug2
    #undef SK_FRAMEWORK_Superkraft

    #ifdef VST2_API
        #undef SK_APP_TYPE_app

        #define SK_APP_TYPE "vst"
        #define SK_APP_TYPE_vst
        #define SK_APP_TYPE_vst2


    #elif defined AU_API
        #undef SK_APP_TYPE_app

        #define SK_APP_TYPE "au"
        #define SK_APP_TYPE_au
        #define SK_APP_TYPE_au1


    #elif defined AUv3_API
        #undef SK_APP_TYPE_app

        #define SK_APP_TYPE "au"
        #define SK_APP_TYPE_au
        #define SK_APP_TYPE_au3


    #elif defined AAX_API
        #undef SK_APP_TYPE_app

        #define SK_APP_TYPE "aax"
        #define SK_APP_TYPE_aax


    #elif defined APP_API
        #undef SK_APP_TYPE_app

        #define SK_APP_TYPE "app"
        #define SK_APP_TYPE_app


    #elif defined WAM_API
        #undef SK_APP_TYPE_app

        #define SK_APP_TYPE "wam"
        #define SK_APP_TYPE_wam


    #elif defined WEB_API
        #undef SK_APP_TYPE_app

        #define SK_APP_TYPE "webapi"
        #define SK_APP_TYPE_webapi


    #elif defined VST3_API
        #undef SK_APP_TYPE_app

        #define SK_APP_TYPE "vst"
        #define SK_APP_TYPE_vst
        #define SK_APP_TYPE_vst3


    #elif defined VST3C_API
        #undef SK_APP_TYPE_app

        #define SK_APP_TYPE "vst"
        #define SK_APP_TYPE_vst
        #define SK_APP_TYPE_vst3


    #elif defined VST3P_API
        #undef SK_APP_TYPE_app

        #define SK_APP_TYPE "vst"
        #define SK_APP_TYPE_vst
        #define SK_APP_TYPE_vst3


    #elif defined CLAP_API
        #undef SK_APP_TYPE_app

        #define SK_APP_TYPE "clap"
        #define SK_APP_TYPE_clap
    #else
    #endif
#endif
