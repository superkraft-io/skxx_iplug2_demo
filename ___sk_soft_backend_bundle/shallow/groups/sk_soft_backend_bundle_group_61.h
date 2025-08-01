#pragma once

#include "../../sk_soft_backend_bundle_group_root.h"

#if defined(SK_BUNDLE_MODE_SHALLOW)
    #include <filesystem>
#endif

BEGIN_SK_NAMESPACE

class SK_SoftBackend_Bundle_Data_Group_61 : public SK_SoftBackend_Bundle_Data_Group_Root {
public:
    unsigned int groupID = 61;
    
    size_t offsets[85] = {0,550,842,6746,7072,8035,8798,11851,12619,18718,21064,59492,59845,65660,65660,65826,65988,68578,68736,70037,70691,79631,79656,83951,84084,87003,87003,87556,87556,141623,141880,142461,143599,147463,148897,151535,151535,155330,155464,157240,157449,157546,158179,163707,168059,169771,173321,173321,174070,174604,179297,179323,179497,179567,205355,205502,205738,205806,206132,206132,206335,208499,208499,208707,208707,208917,208938,209108,210054,218897,218942,219074,219240,221821,221821,222575,222740,225201,225537,227986,228002,229255,229296,229383,229664};
    size_t sizes[85] = {550,292,5904,326,963,763,3053,768,6099,2346,38428,353,5815,0,166,162,2590,158,1301,654,8940,25,4295,133,2919,0,553,0,54067,257,581,1138,3864,1434,2638,0,3795,134,1776,209,97,633,5528,4352,1712,3550,0,749,534,4693,26,174,70,25788,147,236,68,326,0,203,2164,0,208,0,210,21,170,946,8843,45,132,166,2581,0,754,165,2461,336,2449,16,1253,41,87,281,831};
    
    size_t data_size = 230495;
    unsigned char data[230495] = {};

    SK_SoftBackend_Bundle_Data_Group_61() {
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
