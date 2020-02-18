#include "ComponentManager.h"

using namespace EngineECS;


ComponentManager* ComponentManager::Instance = nullptr;

ComponentManager::ComponentManager() :
	idCount(0),
	componentTypeMap(),
	componentStringMap() {

}

ComponentManager::~ComponentManager() {

}

ComponentManager& ComponentManager::GetInstance() {
	if (!Instance) {
		Instance = new ComponentManager();
	}
	return *Instance;
}

int ComponentManager::GenerateIDByType(IComponent* component) {
	//try finding the key in the map
	if (componentTypeMap.find(typeid(component)) != componentTypeMap.end()) {
		//found
		return componentTypeMap[typeid(component)];
	}
	else {
		//not found
		idCount += 1;
		componentTypeMap[typeid(component)] = idCount;
		return idCount;
	}
	return -1;
}

int ComponentManager::GenerateIDByString(const string& label) {
	//try finding the key in the map
	if (componentStringMap.find(label) != componentStringMap.end()) {
		//found
		return componentStringMap[label];
	}
	else {
		//not found
		idCount += 1;
		componentStringMap[label] = idCount;
		return idCount;
	}
	return -1;
}

int ComponentManager::GetIDForType(const type_index type) {
	if (componentTypeMap.find(type) != componentTypeMap.end()) {
		//found
		return componentTypeMap[type];
	}
	return -1;
}

int ComponentManager::GetIDForString(const string& label) {
	if (componentStringMap.find(label) != componentStringMap.end()) {
		//found
		return componentStringMap[label];
	}
	return -1;
}