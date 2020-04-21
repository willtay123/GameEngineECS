#include "ComponentManager.h"

using namespace EngineECS;


ComponentManager* ComponentManager::Instance = nullptr;

ComponentManager::ComponentManager() :
	_idCount(0),
	_typeMap() {

}

ComponentManager::~ComponentManager() {

}

ComponentManager& ComponentManager::GetInstance() {
	if (!Instance) {
		Instance = new ComponentManager();
	}
	return *Instance;
}

int ComponentManager::GenerateIDByType(IComponent const * const component) {
	//try finding the key in the map
	const type_index typing = typeid(component);
	if (_typeMap.find(typing) != _typeMap.end()) {
		//found
		return _typeMap[typing];
	}
	else {
		//not found
		_idCount += 1;
		_typeMap.insert(std::pair<const type_index, const int>(typing, _idCount));
		return _idCount;
	}
}

int ComponentManager::GetIDForType(const type_index type) {
	if (_typeMap.find(type) != _typeMap.end()) {
		//found
		return _typeMap[type];
	}
	return -1;
}