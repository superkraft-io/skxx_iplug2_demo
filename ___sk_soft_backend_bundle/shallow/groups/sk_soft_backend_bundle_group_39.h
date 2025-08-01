#pragma once

#include "../../sk_soft_backend_bundle_group_root.h"

#if defined(SK_BUNDLE_MODE_SHALLOW)
    #include <filesystem>
#endif

BEGIN_SK_NAMESPACE

class SK_SoftBackend_Bundle_Data_Group_39 : public SK_SoftBackend_Bundle_Data_Group_Root {
public:
    unsigned int groupID = 39;
    
    size_t offsets[18] = {0,16887,26847,32304,49560,118406,132113,151425,178372,186314,199889,210474,226995,240024,241100,280510,280999,293229};
    size_t sizes[18] = {16887,9960,5457,17256,68846,13707,19312,26947,7942,13575,10585,16521,13029,1076,39410,489,12230,1500};
    
    size_t data_size = 294729;
    unsigned char data[294729] = {};

    SK_SoftBackend_Bundle_Data_Group_39() {
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
