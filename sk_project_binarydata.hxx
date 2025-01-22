#pragma once

#include "skxx/core/sk_common.hxx"



BEGIN_SK_NAMESPACE

class SK_MS_BDFS_Entry {
public:
    SK_String path;
    SK_String resourceName;

    int ctime = 0;
    int mtime = 0;
    int atime = 0;
    size_t size = 0;
};


class SK_MS_BDFS_Dir : SK_MS_BDFS_Entry {
public:
    SK_String path;
    SK_String dirs;
    SK_String files;


    SK_MS_BDFS_Dir(const SK_String& _path, const SK_String& _dirs, const SK_String& _files) {
        path = _path;
        dirs = _dirs;
        files = _files;
    }

    SK_String toString() {
        return "";
    }
};


class SK_MS_BDFS_File : SK_MS_BDFS_Entry {
public:
    SK_String data;


    SK_MS_BDFS_File(const SK_String& _path, const SK_String& _resourceName = "") {
        path = _path;

        resourceName = _resourceName;

        int dataSize;
        //const auto* data = BinaryData::getNamedResource(resourceName.toUTF8(), dataSize);

        size = size_t(dataSize);
    }

    /*
    WebBrowserComponent::Resource toResource() {
        WebBrowserComponent::Resource resource;

        int dataSize{};
        auto namedResource{BinaryData::getNamedResource(resourceName.toUTF8(), dataSize)};

        resource.data.resize(size);
        std::memcpy(resource.data.data(), namedResource, size);

        resource.mimeType = SK_VB_Helpers_MimeTypes::lookUpMimeType(BinaryData::getNamedResourceOriginalFilename(resourceName.toUTF8()));

        return resource;
    };*/

    SK_String toBase64() {
        return data.toBase64();
    }
};

class SK_Project_BinaryData {
public:
    /*std::pair<SK_String, void*> findEntryByPath(SK_String path) {
        SK_String formattedPath = path;
        SK_String lastCharacter = path.substring(path.length() - 1, path.length());

        if (lastCharacter == "/") formattedPath = path.substring(0, path.length() - 1);

        auto dirQuery = dirEntries.find(formattedPath);
        if (dirQuery != dirEntries.end()) {
            return std::make_pair("dir", dirQuery->second);
        };


        auto fileQuery = fileEntries.find(formattedPath);
        if (fileQuery != fileEntries.end()) {
            return std::make_pair("file", fileQuery->second);
        };

        return std::make_pair("none", nullptr);
    
    }*/


    nlohmann::json readDir(SK_String path) {
        /*auto pair = findEntryByPath(path);

        if (pair.first != "dir") return "{}";

        SK_VB_BDFS_Dir* entry = (SK_VB_BDFS_Dir*)pair.second;


        SSC::JSON::Array json;

        StringArray dirs;
        dirs.addTokens(entry->dirs, ",", "");

        StringArray files;
        files.addTokens(entry->files, ",", "");


        
        for (int i = 0; i < dirs.size(); i++) {
            json.push(SSC::JSON::Object::Entries{
                {"type", "dir"},
                {"name", dirs[i].toStdString()}
            });
        }

        for (int i = 0; i < files.size(); i++) {
            json.push(SSC::JSON::Object::Entries{
                {"type", "file"},
                {"name", files[i].toStdString()}
            });
        }


        return SK_String(json.str());
        */
    }

    std::unordered_map<std::string, SK_MS_BDFS_Dir*> dirEntries {
    };

    std::unordered_map<std::string, SK_MS_BDFS_File*> fileEntries {
    };
};

END_SK_NAMESPACE
