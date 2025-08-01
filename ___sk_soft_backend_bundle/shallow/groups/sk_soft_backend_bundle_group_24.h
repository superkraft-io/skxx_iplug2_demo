#pragma once

#include "../../sk_soft_backend_bundle_group_root.h"

#if defined(SK_BUNDLE_MODE_SHALLOW)
    #include <filesystem>
#endif

BEGIN_SK_NAMESPACE

class SK_SoftBackend_Bundle_Data_Group_24 : public SK_SoftBackend_Bundle_Data_Group_Root {
public:
    unsigned int groupID = 24;
    
    size_t offsets[74] = {0,1987,4063,11765,13734,13837,40330,42751,45289,47581,49705,51118,53049,54775,56452,59138,61180,63794,66513,67700,68481,70767,72685,74154,76669,78341,79783,80300,82937,86928,88842,91449,94216,97139,99672,101784,106980,108836,111015,113384,114072,115019,116765,118853,121293,123097,125175,127253,129738,131252,133053,135062,137502,142839,143590,145530,147299,149738,152178,154342,156484,158615,161648,163903,165787,168862,170863,171487,174609,189944,196561,200134,204559,212249};
    size_t sizes[74] = {1987,2076,7702,1969,103,26493,2421,2538,2292,2124,1413,1931,1726,1677,2686,2042,2614,2719,1187,781,2286,1918,1469,2515,1672,1442,517,2637,3991,1914,2607,2767,2923,2533,2112,5196,1856,2179,2369,688,947,1746,2088,2440,1804,2078,2078,2485,1514,1801,2009,2440,5337,751,1940,1769,2439,2440,2164,2142,2131,3033,2255,1884,3075,2001,624,3122,15335,6617,3573,4425,7690,4367};
    
    size_t data_size = 216616;
    unsigned char data[216616] = {};

    SK_SoftBackend_Bundle_Data_Group_24() {
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
