#include "EntityManager.h"

namespace EngineECS {
	map<const char*, vector<Entity*>*> EntityManager::_entityMap;
	vector<Entity*>* EntityManager::_currentEntityList;
	vector<ToRemove*>* EntityManager::_entitiesToRemove;

	void EntityManager::Initialise() {
		_entitiesToRemove = new vector<ToRemove*>();
	}

	void EntityManager::AddEntity(const char* id, Entity* entity) {
		auto itr = _entityMap.find(id);
		if (itr != _entityMap.end()) {
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
			_entityMap[id] = entityList;
		}
	}

	bool EntityManager::RemoveEntity(const char* mapID, string& entityID) {
		ToRemove* remove = new ToRemove(mapID, entityID);
		_entitiesToRemove->push_back(remove);
		return true;
	}

	void EntityManager::EnactFinal() {
		for (ToRemove* remove : *_entitiesToRemove) {
			const char* mapID = remove->_mapID;
			string entityID = remove->_entity;

			auto itr = _entityMap.find(mapID);
			if (itr != _entityMap.end()) {
				// Entity list match

				// Search entity list for desired entity to delet
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

		for (ToRemove* remove : *_entitiesToRemove) {
			delete remove;
		}
		_entitiesToRemove->clear();
	}

	void EntityManager::SetCurrentByID(const char* id) {
		auto itr = _entityMap.find(id);
		if (itr != _entityMap.end()) {
			// Entity list match
			_currentEntityList = itr->second;
		}
	}

	const vector<Entity*>* EntityManager::GetEntities() {
		return _currentEntityList;
	}

	const vector<Entity*>* EntityManager::GetEntities(const char* id) {
		auto itr = _entityMap.find(id);
		if (itr != _entityMap.end()) {
			// Entity list match
			return itr->second;
		}

		return NULL;
	}

	vector<Entity*>* EntityManager::GetEntitiesEditable(const char* id) {
		auto itr = _entityMap.find(id);
		if (itr != _entityMap.end()) {
			// Entity list match
			return itr->second;
		}

		return NULL;
	}

	vector<Entity*>& EntityManager::GetStartingWith(const char* mapID, string& startString) {
		// List to return
		vector<Entity*>* foundList = new vector<Entity*>();

		// Check for desired entity list in map
		auto itr = _entityMap.find(mapID);
		if (itr != _entityMap.end()) {
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

	const Entity* EntityManager::GetEntity(const char* mapID, const char* entityID) {
		const vector<Entity*>* entityList = GetEntities(mapID);
		for (const Entity* entity : (*entityList)) {
			const string* currentEntityID = entity->GetID();
			if (*currentEntityID == entityID) {
				return entity;
			}
		}
		return NULL;
	}

	Entity* EntityManager::GetEntityEditable(const char* mapID, const char* entityID) {
		vector<Entity*>* entityList = GetEntitiesEditable(mapID);
		for (Entity* entity : (*entityList)) {
			const string* currentEntityID = entity->GetID();
			if (*currentEntityID == entityID) {
				return entity;
			}
		}
		return NULL;
	}

	void EntityManager::End() {
		// Delete all entities of all vectors
		// Delete all vectors
		// Delete map
	}
}