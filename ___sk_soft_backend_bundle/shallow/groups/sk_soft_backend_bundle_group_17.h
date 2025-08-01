#pragma once

#include "../../sk_soft_backend_bundle_group_root.h"

#if defined(SK_BUNDLE_MODE_SHALLOW)
    #include <filesystem>
#endif

BEGIN_SK_NAMESPACE

class SK_SoftBackend_Bundle_Data_Group_17 : public SK_SoftBackend_Bundle_Data_Group_Root {
public:
    unsigned int groupID = 17;
    
    size_t offsets[32] = {0,14891,16574,24938,29603,68493,70628,90954,92561,94308,98699,101101,106332,110607,113032,124377,134228,141897,143979,149982,162761,194084,232962,235224,240863,242164,245814,261738,267602,277680,282356,291079};
    size_t sizes[32] = {14891,1683,8364,4665,38890,2135,20326,1607,1747,4391,2402,5231,4275,2425,11345,9851,7669,2082,6003,12779,31323,38878,2262,5639,1301,3650,15924,5864,10078,4676,8723,2015};
    
    size_t data_size = 293094;
    unsigned char data[293094] = {};

    SK_SoftBackend_Bundle_Data_Group_17() {
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
