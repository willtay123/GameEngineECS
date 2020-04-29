#include "ComponentRigidbody.h"


ComponentRigibody::ComponentRigibody(float gravity) {
	_componentType = ComponentManager::GetInstance().GetIDByType(typeid(ComponentRigibody));
	_isGravityAffected = false;
	_gravityVal = gravity;
	_acceleration = vec3(0, 0, 0);
	_velocity = vec3(0, 0, 0);
}

ComponentRigibody::~ComponentRigibody() {

}

IComponent* ComponentRigibody::Clone() {
	return new ComponentRigibody(_gravityVal);
}

int ComponentRigibody::ComponentType() const {
	return _componentType;
}

void ComponentRigibody::Message(IMessage* message) {
	// nothing to do
}

void ComponentRigibody::SetGravity(float value) {
	_gravityVal = value;
}

float ComponentRigibody::GetGravity() const {
	return _gravityVal;
}

void ComponentRigibody::SetIsGravityAffected(bool isAffected) {
	_isGravityAffected = isAffected;
}

bool ComponentRigibody::IsGravityAffected() const {
	return _isGravityAffected;
}

void ComponentRigibody::SetAcceleration(float x, float y, float z) {
	_acceleration = vec3(x, y, z);
}

const vec3& ComponentRigibody::GetAcceleration() {
	return _acceleration;
}

void ComponentRigibody::SetVelocity(float x, float y, float z) {
	_velocity = vec3(x, y, z);
}

const vec3& ComponentRigibody::GetVelocity() {
	return _velocity;
}