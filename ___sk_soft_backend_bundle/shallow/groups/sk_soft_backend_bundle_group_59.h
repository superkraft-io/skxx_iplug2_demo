#pragma once

#include "../../sk_soft_backend_bundle_group_root.h"

#if defined(SK_BUNDLE_MODE_SHALLOW)
    #include <filesystem>
#endif

BEGIN_SK_NAMESPACE

class SK_SoftBackend_Bundle_Data_Group_59 : public SK_SoftBackend_Bundle_Data_Group_Root {
public:
    unsigned int groupID = 59;
    
    size_t offsets[91] = {0,14170,18122,18440,18524,18608,22929,23569,34567,34863,36002,38229,39980,43272,43516,60929,62594,62727,68162,92741,93765,94385,95031,95717,98203,98853,99234,100470,100562,100866,101685,114003,120973,121609,124700,131159,131570,131636,134878,137230,137601,137729,137947,142639,142749,142803,142885,142952,143057,143429,143521,143594,143704,143786,144214,144340,144440,144519,144598,144734,144936,145016,145133,145237,146714,148395,149403,157144,224425,228711,237178,237481,237588,237778,237881,243061,245377,246131,246353,248014,250068,257503,257570,261108,261431,283903,284217,284438,288392,290657,293273};
    size_t sizes[91] = {14170,3952,318,84,84,4321,640,10998,296,1139,2227,1751,3292,244,17413,1665,133,5435,24579,1024,620,646,686,2486,650,381,1236,92,304,819,12318,6970,636,3091,6459,411,66,3242,2352,371,128,218,4692,110,54,82,67,105,372,92,73,110,82,428,126,100,79,79,136,202,80,117,104,1477,1681,1008,7741,67281,4286,8467,303,107,190,103,5180,2316,754,222,1661,2054,7435,67,3538,323,22472,314,221,3954,2265,2616,3069};
    
    size_t data_size = 296342;
    unsigned char data[296342] = {};

    SK_SoftBackend_Bundle_Data_Group_59() {
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
