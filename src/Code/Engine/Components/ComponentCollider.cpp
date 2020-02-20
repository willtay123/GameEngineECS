#include "ComponentCollider.h"

using namespace EngineECS;


ComponentCollider::ComponentCollider() {
	_componentType = ComponentManager::GetInstance().GenerateIDByType(this);
	_enabled = true;
	_colliderType = string("Undefined Collider");
}

ComponentCollider::ComponentCollider(bool enabled) {
	_enabled = enabled;
	_colliderType = string("Undefined Collider");
}

IComponent* ComponentCollider::Clone() {
	return NULL;
}

int ComponentCollider::ComponentType() const {
	return _componentType;
}

void ComponentCollider::Message(IMessage* message) {

}

const string& ComponentCollider::GetColliderType() {
	return _colliderType;
}

bool ComponentCollider::IsEnabled() {
	return _enabled;
}

void ComponentCollider::SetEnabled(bool enabled) {
	_enabled = enabled;
}