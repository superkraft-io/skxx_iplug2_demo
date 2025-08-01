#pragma once

#include "../../sk_soft_backend_bundle_group_root.h"

#if defined(SK_BUNDLE_MODE_SHALLOW)
    #include <filesystem>
#endif

BEGIN_SK_NAMESPACE

class SK_SoftBackend_Bundle_Data_Group_9 : public SK_SoftBackend_Bundle_Data_Group_Root {
public:
    unsigned int groupID = 9;
    
    size_t offsets[84] = {0,14678,15702,20473,26936,27611,30135,30833,36886,38524,39069,42364,43432,51124,51751,53786,54071,54581,85252,87169,89285,94175,94776,94872,101442,101577,101577,102555,102555,103234,103234,106743,106743,109238,109239,109863,109863,110935,111869,112258,112837,117814,123390,123477,123646,136142,137249,146442,151289,151796,157046,158590,158706,160201,164860,167689,169605,176726,185268,189255,196071,198427,199431,203904,206066,211049,211484,216852,218526,220132,226832,228513,231091,242547,249400,250023,270002,279606,285309,286775,288085,290074,292233,293566};
    size_t sizes[84] = {14678,1024,4771,6463,675,2524,698,6053,1638,545,3295,1068,7692,627,2035,285,510,30671,1917,2116,4890,601,96,6570,135,0,978,0,679,0,3509,0,2495,1,624,0,1072,934,389,579,4977,5576,87,169,12496,1107,9193,4847,507,5250,1544,116,1495,4659,2829,1916,7121,8542,3987,6816,2356,1004,4473,2162,4983,435,5368,1674,1606,6700,1681,2578,11456,6853,623,19979,9604,5703,1466,1310,1989,2159,1333,3035};
    
    size_t data_size = 296601;
    unsigned char data[296601] = {};

    SK_SoftBackend_Bundle_Data_Group_9() {
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
