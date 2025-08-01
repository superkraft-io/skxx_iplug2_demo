#pragma once

#include "../../sk_soft_backend_bundle_group_root.h"

#if defined(SK_BUNDLE_MODE_SHALLOW)
    #include <filesystem>
#endif

BEGIN_SK_NAMESPACE

class SK_SoftBackend_Bundle_Data_Group_19 : public SK_SoftBackend_Bundle_Data_Group_Root {
public:
    unsigned int groupID = 19;
    
    size_t offsets[42] = {0,2165,6780,10552,28313,45861,51620,62329,63182,64704,67802,68795,70641,86097,87736,99353,104492,107054,122318,124102,129483,131858,134201,138487,141415,159442,162573,164485,169029,172994,179835,181192,183865,185796,208816,221152,222933,229853,231237,234377,237553,288570};
    size_t sizes[42] = {2165,4615,3772,17761,17548,5759,10709,853,1522,3098,993,1846,15456,1639,11617,5139,2562,15264,1784,5381,2375,2343,4286,2928,18027,3131,1912,4544,3965,6841,1357,2673,1931,23020,12336,1781,6920,1384,3140,3176,51017,4335};
    
    size_t data_size = 292905;
    unsigned char data[292905] = {};

    SK_SoftBackend_Bundle_Data_Group_19() {
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
