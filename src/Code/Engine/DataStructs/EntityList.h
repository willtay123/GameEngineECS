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
		int size() const { return (int)_entities.size(); }

		template<class Comp>
		const vector<Entity const *> GetEntitiesWithComponent(Comp comp);

		int AddEntity(std::shared_ptr<Entity> entity);
		void RemoveEntity(const string& entityName);

		std::weak_ptr<Entity> GetEntityByName(const string& name);
		std::weak_ptr<Entity> GetEntityByIndex(const int index) {
			return (*this)[index];
		}

		std::weak_ptr<Entity> operator[](const int index) const {
			return _entities[index];
		}
	};
}