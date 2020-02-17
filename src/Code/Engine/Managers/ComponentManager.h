#pragma once

#include <map>
#include <typeindex>
#include <string>

using std::map;
using std::make_pair;
using std::type_index;
using std::string;

namespace EngineECS {
	class IComponent;

	class ComponentManager {
	private:
		static ComponentManager* Instance;

		int idCount;
		map<type_index, int> componentTypeMap;
		map<string, int> componentStringMap;

		ComponentManager();

	public:
		~ComponentManager();
		static ComponentManager& GetInstance();

		int GenerateIDByType(IComponent* component);
		int GenerateIDByString(const string& key);
		int GetIDForType(const type_index type);
		int GetIDForString(const string& label);
	};
}