#pragma once

#include "../../sk_soft_backend_bundle_group_root.h"

#if defined(SK_BUNDLE_MODE_SHALLOW)
    #include <filesystem>
#endif

BEGIN_SK_NAMESPACE

class SK_SoftBackend_Bundle_Data_Group_21 : public SK_SoftBackend_Bundle_Data_Group_Root {
public:
    unsigned int groupID = 21;
    
    size_t offsets[54] = {0,21985,26790,28946,34731,36894,38653,52004,60663,65775,81528,83712,89139,91245,94978,98058,100565,101963,105541,106623,107868,108804,109779,109857,109929,110000,114867,116455,118012,120288,122455,123076,131160,136127,143614,151781,159251,169755,177739,181211,186596,195219,202721,203779,208913,210899,212347,217854,220437,222509,244751,260725,267951,268221};
    size_t sizes[54] = {21985,4805,2156,5785,2163,1759,13351,8659,5112,15753,2184,5427,2106,3733,3080,2507,1398,3578,1082,1245,936,975,78,72,71,4867,1588,1557,2276,2167,621,8084,4967,7487,8167,7470,10504,7984,3472,5385,8623,7502,1058,5134,1986,1448,5507,2583,2072,22242,15974,7226,270,19337};
    
    size_t data_size = 287558;
    unsigned char data[287558] = {};

    SK_SoftBackend_Bundle_Data_Group_21() {
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
