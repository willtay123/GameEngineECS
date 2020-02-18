#pragma once

#include <memory>
#include <string>
#include "Objects/Entity.h"

using std::string;

namespace EngineECS {

	class EntityList {
	private:
		string _listName;
		vector<std::shared_ptr<Entity>> _entities;

	public:

		EntityList(const string& name);
		~EntityList();

		const string& GetName() const;

		template<class Comp>
		const vector<Entity const *> GetEntitiesWithComponent(Comp comp);

		int AddEntity(std::unique_ptr<Entity> entity);
		void RemoveEntity(const string& entityName);

		std::weak_ptr<Entity> GetEntityByName(const string& name);
		std::weak_ptr<Entity> GetEntityByIndex(int index) {
			return _entities[index];
		}
	};
}