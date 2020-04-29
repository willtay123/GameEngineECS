#include "ComponentRigidbody.h"


ComponentRigidbody::ComponentRigidbody(float gravity) {
	_componentType = ComponentManager::GetInstance().GetIDByType(typeid(ComponentRigidbody));
	_isGravityAffected = false;
	_gravityVal = gravity;
	_acceleration = vec3(0, 0, 0);
	_velocity = vec3(0, 0, 0);
}

ComponentRigidbody::~ComponentRigidbody() {

}

IComponent* ComponentRigidbody::Clone() {
	return new ComponentRigidbody(_gravityVal);
}

int ComponentRigidbody::ComponentType() const {
	return _componentType;
}

void ComponentRigidbody::Message(IMessage* message) {
	// nothing to do
}

void ComponentRigidbody::SetGravity(float value) {
	_gravityVal = value;
}

float ComponentRigidbody::GetGravity() const {
	return _gravityVal;
}

void ComponentRigidbody::SetIsGravityAffected(bool isAffected) {
	_isGravityAffected = isAffected;
}

bool ComponentRigidbody::IsGravityAffected() const {
	return _isGravityAffected;
}

void ComponentRigidbody::SetAcceleration(float x, float y, float z) {
	_acceleration = vec3(x, y, z);
}

const vec3& ComponentRigidbody::GetAcceleration() {
	return _acceleration;
}

void ComponentRigidbody::SetVelocity(float x, float y, float z) {
	_velocity = vec3(x, y, z);
}

const vec3& ComponentRigidbody::GetVelocity() {
	return _velocity;
}