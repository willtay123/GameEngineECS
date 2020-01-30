#pragma once

#include <map>
#include <vector>
#include <string>
#include "Objects/Entity.h"

using std::map;
using std::vector;
using std::string;

namespace EngineECS {
	struct ToRemove {
		const char* _mapID;
		string _entity;
		ToRemove(const char* mapID, string entity) {
			_mapID = mapID;
			_entity = entity;
		}
	};

	class EntityManager {
	private:
		static map<const char*, vector<Entity*>*> _entityMap;
		static vector<Entity*>* _currentEntityList;
		static vector<ToRemove*>* _entitiesToRemove;

	public:
		static void Initialise();

		static void AddEntity(const char* id, Entity* entity);
		static bool RemoveEntity(const char* mapID, string& entityID);
		static void EnactFinal();

		static void SetCurrentByID(const char* id);

		static const vector<Entity*>* GetEntities();
		static const vector<Entity*>* GetEntities(const char* id);
		static vector<Entity*>* GetEntitiesEditable(const char* id);
		static vector<Entity*>& GetStartingWith(const char* mapID, string& startString);

		static const Entity* GetEntity(const char* mapID, const char* entityID);
		static Entity* GetEntityEditable(const char* mapID, const char* entityID);

		static void End();
	};
}