#pragma once

#include "../../sk_soft_backend_bundle_group_root.h"

#if defined(SK_BUNDLE_MODE_SHALLOW)
    #include <filesystem>
#endif

BEGIN_SK_NAMESPACE

class SK_SoftBackend_Bundle_Data_Group_10 : public SK_SoftBackend_Bundle_Data_Group_Root {
public:
    unsigned int groupID = 10;
    
    size_t offsets[69] = {0,9985,11240,14663,52706,55247,60436,61801,65042,73116,74420,86469,89242,100736,105364,106946,108293,113756,115897,122111,122299,126155,137867,150099,152606,156453,159746,161618,187837,189046,195153,195505,195576,196825,198214,199152,202372,205125,210032,212977,216526,218228,219868,221244,225533,228023,233810,237273,239830,241560,244124,248185,250394,251864,253725,258549,259908,264090,266239,268319,271789,273281,275699,277983,279326,280715,282947,285213,289740};
    size_t sizes[69] = {9985,1255,3423,38043,2541,5189,1365,3241,8074,1304,12049,2773,11494,4628,1582,1347,5463,2141,6214,188,3856,11712,12232,2507,3847,3293,1872,26219,1209,6107,352,71,1249,1389,938,3220,2753,4907,2945,3549,1702,1640,1376,4289,2490,5787,3463,2557,1730,2564,4061,2209,1470,1861,4824,1359,4182,2149,2080,3470,1492,2418,2284,1343,1389,2232,2266,4527,8177};
    
    size_t data_size = 297917;
    unsigned char data[297917] = {};

    SK_SoftBackend_Bundle_Data_Group_10() {
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
