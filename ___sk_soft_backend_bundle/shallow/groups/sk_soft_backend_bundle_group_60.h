#pragma once

#include "../../sk_soft_backend_bundle_group_root.h"

#if defined(SK_BUNDLE_MODE_SHALLOW)
    #include <filesystem>
#endif

BEGIN_SK_NAMESPACE

class SK_SoftBackend_Bundle_Data_Group_60 : public SK_SoftBackend_Bundle_Data_Group_Root {
public:
    unsigned int groupID = 60;
    
    size_t offsets[52] = {0,5414,6383,50988,70692,75572,76090,76291,76788,76989,79557,80283,80967,83880,84254,84346,87719,88884,90829,94431,96430,101659,101659,107729,110064,116145,132428,135393,156103,162399,164998,171591,174367,185111,185162,188326,189228,193189,193189,199992,200243,201822,204431,205409,264642,267254,287324,290652,295512,295796,298248,298362};
    size_t sizes[52] = {5414,969,44605,19704,4880,518,201,497,201,2568,726,684,2913,374,92,3373,1165,1945,3602,1999,5229,0,6070,2335,6081,16283,2965,20710,6296,2599,6593,2776,10744,51,3164,902,3961,0,6803,251,1579,2609,978,59233,2612,20070,3328,4860,284,2452,114,1315};
    
    size_t data_size = 299677;
    unsigned char data[299677] = {};

    SK_SoftBackend_Bundle_Data_Group_60() {
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
