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

		void AddEntity(const string& groupID, Entity* entity);
		bool RemoveEntity(const string& groupID, const string& entityID);
		void ClearEntityGroup(const string& groupID);
		void ClearEntities();
		void EnactRemovals();

		void SetActiveEntityGroup(const string& groupID);

		const vector<Entity*>* GetEntities();
		const vector<Entity*>* GetEntities(const string& groupID);
		vector<Entity*>* GetEntitiesEditable(const string& groupID);
		vector<Entity*>& GetStartingWith(const string& groupID, const string& startString);

		const Entity* GetEntity(const string& groupID, const string& entityID);
		Entity* GetEntityEditable(const string& mapID, const string& entityID);
	};
}