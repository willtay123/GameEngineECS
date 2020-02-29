#include "EntityList.h"

using namespace EngineECS;

EntityList::EntityList(const string& name) :
	_listName(name) {
}

EntityList::EntityList(const EntityList& other) {
	if (this != &other) {
		_listName = other._listName;
		_entities = other._entities;
	}
}

EntityList& EntityList::operator=(const EntityList& rhs) {
	if (this != &rhs) {
		_listName = rhs._listName;
		_entities = rhs._entities;
	}
	return *this;
}

EntityList::~EntityList() {

}

const string& EntityList::GetName() const {
	return _listName;
}

int EntityList::AddEntity(std::shared_ptr<Entity> entity) {
	if (!entity.get()) {
		return -1;
	}
	_entities->push_back(std::move(entity));
	return _entities->size() - 1;
}

void EntityList::RemoveEntity(const string& name) {
	for (int i = 0; i < (int)_entities->size(); i++) {
		std::shared_ptr<Entity> entity = (*_entities)[i];
		if (entity->GetID() == name) {
			// Remove array index
			_entities->erase(_entities->begin() + i);
		}
	}
}

std::shared_ptr<const Entity> EntityList::GetEntityByName(const string& name) const {
	for (std::shared_ptr<Entity> entity : (*_entities)) {
		if (entity->GetID() == name) {
			return entity;
		}
	}
	return std::shared_ptr<Entity>();
}

std::shared_ptr<Entity> EntityList::GetEditableEntityByName(const string& name) {
	for (std::shared_ptr<Entity> entity : (*_entities)) {
		if (entity->GetID() == name) {
			return entity;
		}
	}
	return std::shared_ptr<Entity>();
}