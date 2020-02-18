#include "EntityList.h"

using namespace EngineECS;

EntityList::EntityList(const string& name) :
	_listName(name) {
}

EntityList::~EntityList() {

}

const string& EntityList::GetName() const {
	return _listName;
}

int EntityList::AddEntity(std::unique_ptr<Entity> entity) {
	if (!entity.get()) {
		return -1;
	}
	_entities.push_back(std::move(entity));
	return _entities.size() - 1;
}

std::weak_ptr<Entity> EntityList::GetEntityByName(const string& name) {
	for (std::shared_ptr<Entity> entity : _entities) {
		return entity;
	}
}