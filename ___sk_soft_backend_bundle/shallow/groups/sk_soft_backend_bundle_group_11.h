#pragma once

#include "../../sk_soft_backend_bundle_group_root.h"

#if defined(SK_BUNDLE_MODE_SHALLOW)
    #include <filesystem>
#endif

BEGIN_SK_NAMESPACE

class SK_SoftBackend_Bundle_Data_Group_11 : public SK_SoftBackend_Bundle_Data_Group_Root {
public:
    unsigned int groupID = 11;
    
    size_t offsets[28] = {0,5012,8052,10879,15410,22937,24489,26541,30666,32513,35455,39143,41040,45062,70820,80130,87186,89978,99490,112895,116370,116760,120844,133142,134933,137860,144440,157395};
    size_t sizes[28] = {5012,3040,2827,4531,7527,1552,2052,4125,1847,2942,3688,1897,4022,25758,9310,7056,2792,9512,13405,3475,390,4084,12298,1791,2927,6580,12955,2996};
    
    size_t data_size = 160391;
    unsigned char data[160391] = {};

    SK_SoftBackend_Bundle_Data_Group_11() {
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
