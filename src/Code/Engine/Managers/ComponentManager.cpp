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

int ComponentManager::GetIDByType(const type_index& typing) {
	//try finding the key in the map
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