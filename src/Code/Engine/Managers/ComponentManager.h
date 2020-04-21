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
		typedef map<const type_index, const int> TypeMap;

		static ComponentManager* Instance;

		int _idCount;
		TypeMap _typeMap;

		ComponentManager();

	public:
		~ComponentManager();
		static ComponentManager& GetInstance();

		int GenerateIDByType(IComponent const * const component);
		int GetIDForType(const type_index type);
	};
}