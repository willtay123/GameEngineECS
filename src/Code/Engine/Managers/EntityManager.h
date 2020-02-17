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
		ToRemove(const string& groupID, const string& entityID) {
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

	public:
		~EntityManager();
		static EntityManager& GetInstance();

		static void AddEntity(const string& groupID, Entity* entity);
		static bool RemoveEntity(const string& groupID, const string& entityID);
		static void ClearEntityGroup(const string& groupID);
		static void ClearEntities();
		static void EnactRemovals();

		static void SetActiveEntityGroup(const string& groupID);

		static const vector<Entity*>* GetEntities();
		static const vector<Entity*>* GetEntities(const string& groupID);
		static vector<Entity*>* GetEntitiesEditable(const string& groupID);
		static vector<Entity*>& GetStartingWith(const string& groupID, const string& startString);

		static const Entity* GetEntity(const string& groupID, const string& entityID);
		static Entity* GetEntityEditable(const string& mapID, const string& entityID);
	};
}