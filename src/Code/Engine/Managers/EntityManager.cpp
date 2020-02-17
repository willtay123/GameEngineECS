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

void EntityManager::AddEntity(const string& groupID, Entity* entity) {
	EntityManager em = GetInstance();

	auto itr = em._entityMap.find(groupID);
	if (itr != em._entityMap.end()) {
		// Entity list match
		vector<Entity*>* entityList = itr->second;
		entityList->push_back(entity);
	}
	else {
		// No Entity list match

		// Create new entity list
		vector<Entity*>* entityList = new vector<Entity*>();
		entityList->push_back(entity);

		// Add entity list to map using the given ID
		em._entityMap[groupID] = entityList;
	}
}

bool EntityManager::RemoveEntity(const string& groupID, const string& entityID) {
	EntityManager em = GetInstance();

	ToRemove remove = ToRemove(groupID, entityID);
	em._entitiesToRemove.push_back(remove);
	return true;
}

void EntityManager::ClearEntityGroup(const string& groupID) {
	EntityManager em = EntityManager::GetInstance();

	auto itr = em._entityMap.find(groupID);
	if (itr != em._entityMap.end()) {
		// Entity list match
		vector<Entity*>* entityList = (itr->second);

		// Delete each entity
		for (int i = 0; i < (int)entityList->size(); i += 1) {
			Entity* entity = (*entityList)[i];
			delete entity;
		}
		delete entityList;
		em._entityMap.erase(groupID);
	}
	else {
		// No Entity list match
	}
}

void EntityManager::ClearEntities() {
	EntityManager em = EntityManager::GetInstance();

	for (auto itr = em._entityMap.begin(); itr != em._entityMap.end(); itr++) {
		vector<Entity*>* entityList = (itr->second);

		// Delete each entity
		for (int i = 0; i < (int)entityList->size(); i += 1) {
			Entity* entity = (*entityList)[i];
			delete entity;
		}
		// Delete vector
		delete entityList;

		// Remove map entry
		em._entityMap.erase(itr);
	}
}

void EntityManager::EnactRemovals() {
	EntityManager em = GetInstance();

	for (ToRemove remove : em._entitiesToRemove) {
		string mapID = remove._groupID;
		string entityID = remove._entityID;

		auto itr = em._entityMap.find(mapID);
		if (itr != em._entityMap.end()) {
			// Entity list match

			// Search entity list for desired entity to delete
			vector<Entity*>* entityList = (itr->second);
			for (int i = 0; i < (int)entityList->size(); i += 1) {
				Entity* entity = (*entityList)[i];
				const string* currentEntityID = entity->GetID();
				if (entityID == *currentEntityID) {
					// Delete matched entity
					delete entity;
					entityList->erase(entityList->begin() + i);
					break;
				}
			}
		}
		else {
			// No Entity list match
		}
	}

	em._entitiesToRemove.clear();
}

void EntityManager::SetActiveEntityGroup(const string& groupID) {
	EntityManager em = GetInstance();

	auto itr = em._entityMap.find(groupID);
	if (itr != em._entityMap.end()) {
		// Entity list match
		em._currentEntityList = itr->second;
	}
}

const vector<Entity*>* EntityManager::GetEntities() {
	EntityManager em = GetInstance();
	return em._currentEntityList;
}

const vector<Entity*>* EntityManager::GetEntities(const string& groupID) {
	EntityManager em = GetInstance();

	auto itr = em._entityMap.find(groupID);
	if (itr != em._entityMap.end()) {
		// Entity list match
		return itr->second;
	}

	return NULL;
}

vector<Entity*>* EntityManager::GetEntitiesEditable(const string& groupID) {
	EntityManager em = GetInstance();

	auto itr = em._entityMap.find(groupID);
	if (itr != em._entityMap.end()) {
		// Entity list match
		return itr->second;
	}

	return NULL;
}

vector<Entity*>& EntityManager::GetStartingWith(const string& groupID, const string& startString) {
	EntityManager em = GetInstance();

	// List to return
	vector<Entity*>* foundList = new vector<Entity*>();

	// Check for desired entity list in map
	auto itr = em._entityMap.find(groupID);
	if (itr != em._entityMap.end()) {
		// Entity list match
		vector<Entity*>* entityList = itr->second;

		for (Entity* entity : *entityList) {
			std::size_t found = entity->GetID()->find(startString);

			if (found == 0) {
				foundList->push_back(entity);
			}
		}
	}
	return *foundList;
}

const Entity* EntityManager::GetEntity(const string& groupID, const string& entityID) {
	const vector<Entity*>* entityList = GetEntities(groupID);
	for (const Entity* entity : (*entityList)) {
		const string* currentEntityID = entity->GetID();
		if (*currentEntityID == entityID) {
			return entity;
		}
	}
	return NULL;
}

Entity* EntityManager::GetEntityEditable(const string& groupID, const string& entityID) {
	vector<Entity*>* entityList = GetEntitiesEditable(groupID);
	for (Entity* entity : (*entityList)) {
		const string* currentEntityID = entity->GetID();
		if (*currentEntityID == entityID) {
			return entity;
		}
	}
	return NULL;
}