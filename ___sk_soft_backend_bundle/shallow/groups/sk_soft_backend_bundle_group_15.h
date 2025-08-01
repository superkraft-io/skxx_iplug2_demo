#pragma once

#include "../../sk_soft_backend_bundle_group_root.h"

#if defined(SK_BUNDLE_MODE_SHALLOW)
    #include <filesystem>
#endif

BEGIN_SK_NAMESPACE

class SK_SoftBackend_Bundle_Data_Group_15 : public SK_SoftBackend_Bundle_Data_Group_Root {
public:
    unsigned int groupID = 15;
    
    size_t offsets[33] = {0,37230,47788,76314,81777,97166,99901,118872,121473,125633,135956,144048,154084,176569,181164,187863,200726,203339,244185,247022,247483,249702,253774,255682,258490,261670,269191,276319,278292,279636,287340,293680,294094};
    size_t sizes[33] = {37230,10558,28526,5463,15389,2735,18971,2601,4160,10323,8092,10036,22485,4595,6699,12863,2613,40846,2837,461,2219,4072,1908,2808,3180,7521,7128,1973,1344,7704,6340,414,5488};
    
    size_t data_size = 299582;
    unsigned char data[299582] = {};

    SK_SoftBackend_Bundle_Data_Group_15() {
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
