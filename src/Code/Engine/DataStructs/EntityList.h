#pragma once

#include <string>
#include "Objects/Entity.h"
#include "CleverPointers.h"

using std::string;

namespace EngineECS {

	class EntityList {
	private:
		typedef vector<shared_ptr<Entity>> EntityData;

		string _listName;
		shared_ptr<EntityData> _entities;

	public:

		EntityList(const string& name);
		EntityList(const EntityList& other);
		EntityList& operator=(const EntityList& rhs);
		~EntityList();

		const string& GetName() const;
		int size() const { return (int)_entities->size(); }

		template<class Comp>
		const vector<Entity const *> GetEntitiesWithComponent(Comp comp);

		int AddEntity(std::shared_ptr<Entity> entity);
		void RemoveEntity(const string& entityName);

		std::shared_ptr<const Entity> GetEntityByName(const string& name) const;
		std::shared_ptr<Entity> GetEditableEntityByName(const string& name);
		std::shared_ptr<Entity> GetEntityByIndex(const int index) {
			return (*this)[index];
		}

		// Operators
		std::shared_ptr<Entity> operator[](const int index) const {
			return (*_entities)[index];
		}
	};
}