#pragma once
#include <rapidjson/document.h>
#include <string>

namespace viper::Json {

		
		bool Load(const std::string& filename, rapidjson::Document& document);

		bool Read(const rapidjson::Value& value, const std::string& name, int& data);
	
	
}