#pragma once
#include "Framework/System.h"
#include "Resource/Resource.h"
#include <string>
#include <map>
#include <memory>
#include <algorithm>

namespace PhoenixEngine
{
	class ResourceSystem : public System
	{
	public:
		void Startup() override {}
		void Shutdown() override {}
		void Update(float dt) override {}

		void Add(const std::string& name, std::shared_ptr<PhoenixEngine::Resource> resource);

		template <typename T>
		std::shared_ptr<T> Get(const std::string& name, void* data = nullptr);

		template <typename T>
		std::vector<std::shared_ptr<T>> Get();

	private:
		std::map<std::string, std::shared_ptr<Resource>> resources;
	};
	
	template<typename T>
	inline std::shared_ptr<T> ResourceSystem::Get(const std::string& name, void* data)
	{
		if (resources.find(string_tolower(name)) != resources.end())
		{
			return std::dynamic_pointer_cast<T>(resources[string_tolower(name)]);
		}
		else
		{
			std::shared_ptr<T> resource = std::make_shared<T>();
			resource->Load(name, data);
			resources[string_tolower(name)] = resource;

			return resource;
		}
	}

	template <typename T>
	inline std::vector<std::shared_ptr<T>> ResourceSystem::Get()
	{
		std::vector<std::shared_ptr<T>> result;

		for (auto& element : resources)
		{
			// get the value of the map (first = key, second = value)
			// the value is a shared_ptr, get() the raw pointer and try to cast to type T*
			if (dynamic_cast<T*>(element.second.get()))
			{
				// if it is of type T, add the shared pointer to the vector
				result.push_back(std::dynamic_pointer_cast<T>(element.second));
			}
		}

		return result;
	}

	inline void ResourceSystem::Add(const std::string& name, std::shared_ptr<PhoenixEngine::Resource> resource)
	{
		resources[string_tolower(name)] = resource;
	}
}