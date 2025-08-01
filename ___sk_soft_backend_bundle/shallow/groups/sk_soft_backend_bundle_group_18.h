#pragma once

#include "../../sk_soft_backend_bundle_group_root.h"

#if defined(SK_BUNDLE_MODE_SHALLOW)
    #include <filesystem>
#endif

BEGIN_SK_NAMESPACE

class SK_SoftBackend_Bundle_Data_Group_18 : public SK_SoftBackend_Bundle_Data_Group_Root {
public:
    unsigned int groupID = 18;
    
    size_t offsets[47] = {0,6934,11252,18167,21994,25284,29488,32088,37442,42695,52860,54632,62688,65128,72170,74025,78551,79902,86563,87995,92200,94082,97652,99186,155268,157260,175597,182235,183718,189529,197007,209926,212892,214455,216627,219261,221451,223932,239921,243189,250762,257029,271953,274801,283754,290348,292874};
    size_t sizes[47] = {6934,4318,6915,3827,3290,4204,2600,5354,5253,10165,1772,8056,2440,7042,1855,4526,1351,6661,1432,4205,1882,3570,1534,56082,1992,18337,6638,1483,5811,7478,12919,2966,1563,2172,2634,2190,2481,15989,3268,7573,6267,14924,2848,8953,6594,2526,6738};
    
    size_t data_size = 299612;
    unsigned char data[299612] = {};

    SK_SoftBackend_Bundle_Data_Group_18() {
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
