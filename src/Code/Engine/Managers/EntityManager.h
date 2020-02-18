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
		typedef map<string, EntityList*> EntityMap;

		static EntityManager* Instance;
		EntityMap _entityMap;
		EntityList* _currentEntityList;
		vector<ToRemove> _entitiesToRemove;

		EntityManager();

	public:
		~EntityManager();
		static EntityManager& GetInstance();

		int AddEntity(const string& groupID, std::unique_ptr<Entity> entity);
		bool RemoveEntity(const string& groupID, const string& entityID);

		void ClearEntityGroup(const string& groupID);
		void ClearEntities();
		void EnactRemovals();

		void SetActiveEntityGroup(const string& groupID);

		const EntityList& GetEntities();
		const EntityList& GetEntities(const string& groupID);

		const std::weak_ptr<Entity> GetEntity(const string& groupID, const string& entityID);
		std::weak_ptr<Entity> GetEntityEditable(const string& groupID, const string& entityID);
	};
}