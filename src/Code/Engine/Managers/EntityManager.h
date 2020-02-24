#pragma once

#include <map>
#include <vector>
#include <string>
#include <memory>
#include "DataStructs/EntityList.h"
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
		typedef map<string, std::shared_ptr<EntityList>> EntityMap;

		static EntityManager* Instance;
		EntityMap _entityMap;
		string _currentGroupID;
		vector<ToRemove> _entitiesToRemove;

		EntityManager();

	public:
		~EntityManager();
		static EntityManager& GetInstance();

		int AddEntity(const string& groupID, std::unique_ptr<Entity> entity);
		bool RemoveEntity(const string& groupID, const string& entityID);

		void ClearEntityGroup(const string& groupID);
		void ClearCurrentEntities();
		void ClearAllEntities();
		void EnactRemovals();

		int GetEntityCount(const string& groupID);

		void SetActiveEntityGroup(const string& groupID);

		std::weak_ptr<EntityList> GetEntities();
		std::weak_ptr<EntityList> GetEntities(const string& groupID);

		const std::weak_ptr<Entity> GetEntity(const string& groupID, const string& entityID);
		std::weak_ptr<Entity> GetEntityEditable(const string& groupID, const string& entityID);
	};
}