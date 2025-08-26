#pragma once
#include "Core/StringHelper.h"
#include "Singleton.h"
#include "Resource.h"
#include "Logger.h"
#include <string>
#include <iostream>
#include <map>


namespace viper {
	class ResourceManager : public Singleton<ResourceManager> {
	public:

		void Clear() { m_resources.clear(); }

		template<typename T, typename ... Args>
		requires std::derived_from<T, Resource>
		res_t<T> Get(const std::string& name, Args&& ... args);

		template<typename T, typename ...Args>
		requires std::derived_from<T, Resource>

		res_t<T> GetWithID(const std::string& id, const std::string name, Args&& ...args);

		

		

		static ResourceManager& Instance() {
			static ResourceManager instance;
			return instance;

		}
	
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;

		std::map<std::string, res_t<Resource>> m_resources;

	};

	template<typename T, typename ...Args>
	inline res_t<T> Get(const std::string& id, std::string name, Args && ...args) {
		return GetWithID<T>(name, name, std::forward<Args>(args)...);
	}
	template<typename T, typename ... Args>
	requires std::derived_from<T, Resource>
	inline res_t<T> ResourceManager::Get(const std::string& name, Args&& ... args)
	{
		std::string key = tolower(name);

		auto iter = m_resources.find(key);
		if (iter != m_resources.end()) {
			//get value in iterator
			auto base = iter->second;
			//cast to data type t
			auto resource = std::dynamic_pointer_cast<T>(base);
			//check if cast was successful
			if (resource == nullptr) {
				Logger::Error("Resource type mismatch: ", key);
				
				return res_t<T>();
			}

			//return resource
			return resource;
		}

		//load resource
		res_t<T> resource = std::make_shared<T>();
		if (resource->Load(key, std::forward<Args>(args)...) == false) {
			Logger::Error("Could not load resource: ", key);
			return res_t<T>();

		}


		//add resource to resource manager
		m_resources[key] = resource;

		return resource;
	}
	template<typename T, typename ...Args>
	requires std::derived_from<T, Resource>

	inline res_t<T> ResourceManager::GetWithID(const std::string& id, const std::string name, Args&& ...args) {
		std::string key = tolower(id);

		auto iter = m_resources.find(key);
		if (iter != m_resources.end()) {
			//get value in iterator
			auto base = iter->second;
			//cast to data type t
			auto resource = std::dynamic_pointer_cast<T>(base);
			//check if cast was successful
			if (resource == nullptr) {
				Logger::Error("Resource type mismatch: ", key);

				return res_t<T>();
			}

			//return resource
			return resource;
		}

		//load resource
		res_t<T> resource = std::make_shared<T>();
		if (resource->Load(name, std::forward<Args>(args)...) == false) {
			Logger::Error("Could not load resource: ", key);
			return res_t<T>();

		}


		//add resource to resource manager
		m_resources[key] = resource;

		return resource;
	
	}
	inline ResourceManager& Resources() {
		return ResourceManager::Instance();
	}

}