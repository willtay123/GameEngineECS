#include "EntityManager.h"

using namespace EngineECS;


EntityManager* EntityManager::Instance = nullptr;

EntityManager::EntityManager() :
	_entityMap(),
	_currentGroupID(),
	_entitiesToRemove() {

}

EntityManager::~EntityManager() {
	ClearAllEntities();
}

EntityManager& EntityManager::GetInstance() {
	if (!Instance) {
		Instance = new EntityManager();
	}
	return *Instance;
}

int EntityManager::AddEntity(const string& groupID, std::shared_ptr<Entity> entity) {
	int index = -1;

	// Get or create an EntityList
	auto itr = _entityMap.find(groupID);
	if (itr != _entityMap.end()) {
		// Entity List match
		std::shared_ptr<EntityList> entityList = itr->second;
		index = entityList->AddEntity(entity);
	}
	else {
		// No Entity List match

		// If it is the first list, make it the current list
		if (_entityMap.size() == 0) {
			_currentGroupID = groupID;
		}

		// Create new entity list
		std::shared_ptr<EntityList> entityList(new EntityList(groupID));
		index = entityList->AddEntity(entity);

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
		_entityMap.erase(groupID);
	}
}

void EntityManager::ClearCurrentEntities() {
	EntityManager::ClearEntityGroup(_currentGroupID);
}

void EntityManager::ClearAllEntities() {
	_entityMap.clear();
}

int EntityManager::GetEntityCount(const string& groupID) {
	auto entities = GetEntities(groupID);
	int count = entities->size();
	return count;
}

void EntityManager::EnactRemovals() {
	for (ToRemove remove : _entitiesToRemove) {
		string mapID = remove._groupID;
		string entityID = remove._entityID;

		auto itr = _entityMap.find(mapID);
		if (itr != _entityMap.end()) {
			// Entity list match

			// Search entity list for desired entity to delete
			std::weak_ptr<EntityList> entityList = itr->second;
			entityList.lock()->RemoveEntity(entityID);
		}
		else {
			// No Entity list match
		}
	}
	_entitiesToRemove.clear();
}

void EntityManager::SetActiveEntityGroup(const string& groupID) {
	_currentGroupID = groupID;
}

// Getting Entities
std::shared_ptr<const EntityList> EntityManager::GetEntities() {
	return GetEntitiesEditable(_currentGroupID);
}
std::shared_ptr<const EntityList> EntityManager::GetEntities(const string& groupID) { //Problem, doesnt return all
	return GetEntitiesEditable(groupID);
}
std::shared_ptr<EntityList> EntityManager::GetEntitiesEditable() {
	return GetEntitiesEditable(_currentGroupID);
}
std::shared_ptr<EntityList> EntityManager::GetEntitiesEditable(const string& groupID) {
	auto itr = _entityMap.find(groupID);
	if (itr != _entityMap.end()) {
		// Entity list match
		return itr->second;
	}
	return std::shared_ptr<EntityList>();
}

const std::shared_ptr<const Entity> EntityManager::GetEntity(const string& groupID, const string& entityID) {
	std::shared_ptr<const EntityList> entityList = GetEntities(groupID);
	return entityList->GetEntityByName(entityID);
}

std::shared_ptr<Entity> EntityManager::GetEntityEditable(const string& groupID, const string& entityID) {
	std::shared_ptr<EntityList> entityList = GetEntitiesEditable(groupID);
	return entityList->GetEditableEntityByName(entityID);
}