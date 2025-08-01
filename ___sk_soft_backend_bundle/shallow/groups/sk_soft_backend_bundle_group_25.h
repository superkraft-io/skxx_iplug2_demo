#pragma once

#include "../../sk_soft_backend_bundle_group_root.h"

#if defined(SK_BUNDLE_MODE_SHALLOW)
    #include <filesystem>
#endif

BEGIN_SK_NAMESPACE

class SK_SoftBackend_Bundle_Data_Group_25 : public SK_SoftBackend_Bundle_Data_Group_Root {
public:
    unsigned int groupID = 25;
    
    size_t offsets[56] = {0,134617,140170,144913,144913,144968,146152,146783,147112,147795,147977,148194,148345,149499,149499,149606,149808,150069,150907,154678,155728,161198,165829,166024,166179,166704,167556,169809,180753,181357,183793,184535,186684,187284,189645,192325,201885,202421,203148,203467,204178,204360,204577,204728,205873,216809,221132,236441,243828,244784,246215,251303,260224,269506,269773,276116};
    size_t sizes[56] = {134617,5553,4743,0,55,1184,631,329,683,182,217,151,1154,0,107,202,261,838,3771,1050,5470,4631,195,155,525,852,2253,10944,604,2436,742,2149,600,2361,2680,9560,536,727,319,711,182,217,151,1145,10936,4323,15309,7387,956,1431,5088,8921,9282,267,6343,7570};
    
    size_t data_size = 283686;
    unsigned char data[283686] = {};

    SK_SoftBackend_Bundle_Data_Group_25() {
        getPointersCB = [this](void** _offsets, void** _sizes, void** _data, size_t* _data_size) {
            *_offsets = (void*)this->offsets;  // Assign address of `offsets`
            *_sizes = (void*)this->sizes;     // Assign address of `sizes`
            *_data = (void*)this->data;       // Assign address of `data`
            *_data_size = this->data_size;    // Assign data size
        };

        #if defined(SK_BUNDLE_MODE_SHALLOW)
            loadShallowData();
        #endif
    };


    #if defined(SK_BUNDLE_MODE_SHALLOW)
        bool loadShallowData(){
            //Load shallow data
            SK_String path = SK_BUNDLER_SHALLOW_DATA_PATH + "/" + SK_String(groupID) + ".bin";

            FILE* file = fopen(path.replaceAll("\\", "/").c_str(), "rb");
            if (file) {
                fseek(file, 0, SEEK_END);
                long dataSize = ftell(file);
                char* buffer = (char*)malloc(dataSize + 1);
                fseek(file, 0, SEEK_SET);
                fread(buffer, 1, dataSize, file);

                std::memcpy(data, buffer, dataSize);

                free(buffer);

                fclose(file);

                return true;
            }

            return false;
        }
    #endif
};

END_SK_NAMESPACE
