#include "EntityManager.h"

using namespace EngineECS;


EntityManager* EntityManager::Instance;

EntityManager::EntityManager() :
	_entityMap(),
	_currentEntityList(nullptr),
	_entitiesToRemove() {

}

EntityManager::~EntityManager() {
	ClearEntities();
}

EntityManager& EntityManager::GetInstance() {
	if (!Instance) {
		Instance = new EntityManager();
	}
	return *Instance;
}

int EntityManager::AddEntity(const string& groupID, std::unique_ptr<Entity> entity) {
	int index = -1;

	// Get or create an EntityList
	auto itr = _entityMap.find(groupID);
	if (itr != _entityMap.end()) {
		// Entity List match
		EntityList* entityList = itr->second;
		index = entityList->AddEntity(std::move(entity));
	}
	else {
		// No Entity List match

		// Create new entity list
		EntityList* entityList = new EntityList(groupID);
		index = entityList->AddEntity(std::move(entity));

		// Add entity list to map using the given ID
		_entityMap[groupID] = entityList;
	}
	return index;
}

bool EntityManager::RemoveEntity(const string& groupID, const string& entityID) {
	ToRemove remove = ToRemove(groupID, entityID);
	_entitiesToRemove.push_back(remove);
	return true;
}

void EntityManager::ClearEntityGroup(const string& groupID) {
	auto itr = _entityMap.find(groupID);
	if (itr != _entityMap.end()) {
		// Entity list match
		EntityList* entityList = itr->second;
		delete entityList;
		_entityMap.erase(groupID);
	}
	else {
		// No Entity list match
	}
}

void EntityManager::ClearEntities() {
	for (auto itr = _entityMap.begin(); itr != _entityMap.end(); itr++) {
		EntityList* entityList = itr->second;
		delete entityList;
		_entityMap.erase(itr);
	}
}

void EntityManager::EnactRemovals() {
	for (ToRemove remove : _entitiesToRemove) {
		string mapID = remove._groupID;
		string entityID = remove._entityID;

		auto itr = _entityMap.find(mapID);
		if (itr != _entityMap.end()) {
			// Entity list match

			// Search entity list for desired entity to delete
			EntityList* entityList = itr->second;
			entityList->RemoveEntity(entityID);
		}
		else {
			// No Entity list match
		}
	}
	_entitiesToRemove.clear();
}

void EntityManager::SetActiveEntityGroup(const string& groupID) {
	auto itr = _entityMap.find(groupID);
	if (itr != _entityMap.end()) {
		// Entity list match
		_currentEntityList = itr->second;
	}
}

const EntityList& EntityManager::GetEntities() { //problem if null
	return *_currentEntityList;
}

const EntityList& EntityManager::GetEntities(const string& groupID) { //Problem, doesnt return all
	auto itr = _entityMap.find(groupID);
	if (itr != _entityMap.end()) {
		// Entity list match
		return *(itr->second);
	}
}

const std::weak_ptr<Entity> EntityManager::GetEntity(const string& groupID, const string& entityID) {
	EntityList entityList = GetEntities(groupID);
	return entityList.GetEntityByName(entityID);
}

std::weak_ptr<Entity> EntityManager::GetEntityEditable(const string& groupID, const string& entityID) {
	EntityList entityList = GetEntities(groupID);
	return entityList.GetEntityByName(entityID);
}