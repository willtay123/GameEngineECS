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
		string _mapID;
		string _entity;
		ToRemove(string mapID, string entity) {
			_mapID = mapID;
			_entity = entity;
		}
	};

	class EntityManager {
	private:
		static map<string, vector<Entity*>*> _entityMap;
		static vector<Entity*>* _currentEntityList;
		static vector<ToRemove*>* _entitiesToRemove;

	public:
		static void Initialise();

		static void AddEntity(string id, Entity* entity);
		static bool RemoveEntity(string mapID, string& entityID);
		static void EnactFinal();

		static void SetCurrentByID(string id);

		static const vector<Entity*>* GetEntities();
		static const vector<Entity*>* GetEntities(string id);
		static vector<Entity*>* GetEntitiesEditable(string id);
		static vector<Entity*>& GetStartingWith(string mapID, string& startString);

		static const Entity* GetEntity(string mapID, string entityID);
		static Entity* GetEntityEditable(string mapID, string entityID);

		static void End();
	};
}