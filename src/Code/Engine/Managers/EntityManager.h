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
		string _groupID;
		string _entityID;
		ToRemove(string& groupID, string& entityID) {
			_groupID = groupID;
			_entityID = entityID;
		}
	};

	class EntityManager {
	private:
		static EntityManager* Instance;
		map<string, vector<Entity*>*> _entityMap;
		vector<Entity*>* _currentEntityList;
		vector<ToRemove> _entitiesToRemove;

		EntityManager();
		~EntityManager();

	public:
		static EntityManager& GetInstance();

		static void AddEntity(string& groupID, Entity* entity);
		static bool RemoveEntity(string& groupID, string& entityID);
		static void ClearEntityGroup(string& groupID);
		static void ClearEntities();
		static void EnactRemovals();

		static void SetActiveEntityGroup(string& groupID);

		static const vector<Entity*>* GetEntities();
		static const vector<Entity*>* GetEntities(string& groupID);
		static vector<Entity*>* GetEntitiesEditable(string& groupID);
		static vector<Entity*>& GetStartingWith(string& groupID, string& startString);

		static const Entity* GetEntity(string& groupID, string& entityID);
		static Entity* GetEntityEditable(string& mapID, string& entityID);
	};
}