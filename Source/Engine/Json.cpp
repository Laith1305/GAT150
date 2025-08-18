#include "Json.h"
#include "Core/File.h"
#include "Logger.h"
#include <rapidjson/istreamwrapper.h>
#include <iostream>

namespace viper::Json
{
    bool Load(const std::string& filename, rapidjson::Document& document) {
        // read the file into a string
        std::string buffer;
        if (!file::ReadTextFile(filename, buffer)) {
            Logger::Error("Could not read file: {}.", filename);
            return false;
        }

        // convert the string into a json stream
        std::stringstream stream(buffer);
        rapidjson::IStreamWrapper istream(stream);

        // set the json document from the stream
        document.ParseStream(istream);
        // check if the parse was successful
        if (!document.IsObject()) {
            Logger::Error("Could not parse Json: {}.", filename);
            return false;
        }

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, int& data) {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt()) {
            Logger::Error("Could not read Json value (int): {}.", name);
            return false;
        }

        // get the data
        data = value[name.c_str()].GetInt();

        return true;
    }
}