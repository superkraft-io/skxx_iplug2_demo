#pragma once

#include "../../sk_soft_backend_bundle_group_root.h"

#if defined(SK_BUNDLE_MODE_SHALLOW)
    #include <filesystem>
#endif

BEGIN_SK_NAMESPACE

class SK_SoftBackend_Bundle_Data_Group_16 : public SK_SoftBackend_Bundle_Data_Group_Root {
public:
    unsigned int groupID = 16;
    
    size_t offsets[59] = {0,1635,2774,7191,18983,21052,25791,28050,33280,38093,41422,51535,64559,67298,73368,75810,84654,86071,89816,103022,108651,110283,129157,131317,134874,136906,141610,144714,149945,151736,160368,162852,171997,173845,178949,182601,189471,202729,204303,210334,212516,220500,222685,228040,230119,233130,235536,237831,245996,248182,249573,258955,276519,279088,280809,282887,288573,292000,294796};
    size_t sizes[59] = {1635,1139,4417,11792,2069,4739,2259,5230,4813,3329,10113,13024,2739,6070,2442,8844,1417,3745,13206,5629,1632,18874,2160,3557,2032,4704,3104,5231,1791,8632,2484,9145,1848,5104,3652,6870,13258,1574,6031,2182,7984,2185,5355,2079,3011,2406,2295,8165,2186,1391,9382,17564,2569,1721,2078,5686,3427,2796,1385};
    
    size_t data_size = 296181;
    unsigned char data[296181] = {};

    SK_SoftBackend_Bundle_Data_Group_16() {
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
