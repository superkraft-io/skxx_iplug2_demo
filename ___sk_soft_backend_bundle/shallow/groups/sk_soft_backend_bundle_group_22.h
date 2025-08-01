#pragma once

#include "../../sk_soft_backend_bundle_group_root.h"

#if defined(SK_BUNDLE_MODE_SHALLOW)
    #include <filesystem>
#endif

BEGIN_SK_NAMESPACE

class SK_SoftBackend_Bundle_Data_Group_22 : public SK_SoftBackend_Bundle_Data_Group_Root {
public:
    unsigned int groupID = 22;
    
    size_t offsets[48] = {0,13921,16678,22226,28738,29752,34842,44977,59283,60811,61064,75413,77986,106832,107882,125223,127452,139680,145036,149301,157630,160500,171724,174626,182699,185940,188739,197247,199101,202410,205672,208666,215741,217895,220060,224686,228724,240077,244189,250751,253083,264256,264736,265102,272194,282618,284129,288899};
    size_t sizes[48] = {13921,2757,5548,6512,1014,5090,10135,14306,1528,253,14349,2573,28846,1050,17341,2229,12228,5356,4265,8329,2870,11224,2902,8073,3241,2799,8508,1854,3309,3262,2994,7075,2154,2165,4626,4038,11353,4112,6562,2332,11173,480,366,7092,10424,1511,4770,3536};
    
    size_t data_size = 292435;
    unsigned char data[292435] = {};

    SK_SoftBackend_Bundle_Data_Group_22() {
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
