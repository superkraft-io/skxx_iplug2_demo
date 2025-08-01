#pragma once

#include "../../sk_soft_backend_bundle_group_root.h"

#if defined(SK_BUNDLE_MODE_SHALLOW)
    #include <filesystem>
#endif

BEGIN_SK_NAMESPACE

class SK_SoftBackend_Bundle_Data_Group_20 : public SK_SoftBackend_Bundle_Data_Group_Root {
public:
    unsigned int groupID = 20;
    
    size_t offsets[46] = {0,7796,11498,13978,56549,58319,65841,75267,81572,86517,90872,100312,114148,118719,118939,127449,129163,129602,138065,139897,142795,144590,147087,151560,153953,157493,167649,171304,179162,180698,185548,187005,191571,193040,202877,204386,218182,221490,228619,231230,243551,273335,275813,282518,284588,287473};
    size_t sizes[46] = {7796,3702,2480,42571,1770,7522,9426,6305,4945,4355,9440,13836,4571,220,8510,1714,439,8463,1832,2898,1795,2497,4473,2393,3540,10156,3655,7858,1536,4850,1457,4566,1469,9837,1509,13796,3308,7129,2611,12321,29784,2478,6705,2070,2885,1781};
    
    size_t data_size = 289254;
    unsigned char data[289254] = {};

    SK_SoftBackend_Bundle_Data_Group_20() {
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
