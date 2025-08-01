#pragma once

#include "../../sk_soft_backend_bundle_group_root.h"

#if defined(SK_BUNDLE_MODE_SHALLOW)
    #include <filesystem>
#endif

BEGIN_SK_NAMESPACE

class SK_SoftBackend_Bundle_Data_Group_58 : public SK_SoftBackend_Bundle_Data_Group_Root {
public:
    unsigned int groupID = 58;
    
    size_t offsets[50] = {0,93570,96227,98348,100160,189661,193705,196458,198362,199999,200066,200138,200198,204537,227357,230629,235076,238080,238866,243115,243332,248884,250044,251356,251902,255239,256028,256206,257810,258369,260633,262730,262898,263260,263891,264270,264514,273693,274223,276225,277881,278751,279068,281372,285465,285553,285954,287238,287361,287492};
    size_t sizes[50] = {93570,2657,2121,1812,89501,4044,2753,1904,1637,67,72,60,4339,22820,3272,4447,3004,786,4249,217,5552,1160,1312,546,3337,789,178,1604,559,2264,2097,168,362,631,379,244,9179,530,2002,1656,870,317,2304,4093,88,401,1284,123,131,501};
    
    size_t data_size = 287993;
    unsigned char data[287993] = {};

    SK_SoftBackend_Bundle_Data_Group_58() {
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
