#pragma once
#include "Entity.h"

using namespace EngineECS;

Entity::Entity() :
	_id("Undefined"),
	_enabled(true),
	_components(new vector<IComponent*>()) {
}

Entity::Entity(const string& id) :
	_id(id),
	_enabled(true),
	_components(new vector<IComponent*>()) {

}

Entity::Entity(const Entity& rhs) :
	_id(rhs._id),
	_enabled(rhs._enabled) {
	_components = new vector<IComponent*>();
	for (IComponent* component : *(rhs._components)) {
		IComponent* clone = component->Clone();
		_components->push_back(clone);
	}
}

Entity& Entity::operator=(const Entity& rhs) {
	if (&rhs != this) {
		_id = rhs._id;
		_enabled = rhs._enabled;
		_components = rhs._components;
	}
	return *this;
}

Entity::~Entity() {
	if (_components->size() > 0) {
		for (IComponent* component : (*_components)) {
			delete component;
		}
	}
	_components->clear();
}

const string& Entity::GetID() const {
	return _id;
}

void Entity::SetID(string value) {
	_id = value;
}

void Entity::AddComponent(IComponent* component) {
	_components->push_back(component);
}

void Entity::RemoveComponent(int id) {
	int index;
	bool hasComponent = GetComponentIndex(id, &index);

	if (hasComponent) {
		_components->erase(_components->begin() + index);
	}
}

bool Entity::HasComponent(int id) {
	for (IComponent* component : (*_components)) {
		//	if match, return true
		//if (component->id == id) { return true; }
	}
	return false;
}

const vector<IComponent*>* Entity::GetComponents() const {
	return _components;
}

vector<IComponent*>* Entity::GetComponentsEditable() {
	return _components;
}

const IComponent* Entity::GetComponent(int id) const {
	for (IComponent* component : (*_components)) {
		int currentID = component->ComponentType();
		if (currentID == id) {
			return component;
		}
	}
	return NULL;
}

const IComponent* Entity::GetComponent(string id) const {
	int searchID = ComponentManager::GetInstance().GetIDForString(id);
	return GetComponent(searchID);
}

IComponent* Entity::GetComponentEditable(int id) {
	for (IComponent* component : (*_components)) {
		int currentID = component->ComponentType();
		if (currentID == id) {
			return component;
		}
	}
	return NULL;
}

void Entity::Message(IMessage* message) {
	for (IComponent* component : (*_components)) {
		//NOTE: may call the base method instead of dynamically typing
		component->Message(message);
	}
}

bool Entity::GetComponentIndex(int id, int* outIndex) {
	for (size_t i = 0, length = _components->size(); i < length; i += 1) {
		//if (component->id == id) { 
		//	*outIndex = (int)i;
		//	return true;
		//}
	}
	return false;
}