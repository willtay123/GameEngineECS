#include "ComponentPhysics.h"


ComponentPhysics::ComponentPhysics(float gravity) {
	_componentType = ComponentManager::GetInstance().GetIDByType(typeid(ComponentPhysics));
	_isGravityAffected = false;
	_gravityVal = gravity;
	_acceleration = vec3(0, 0, 0);
	_velocity = vec3(0, 0, 0);
}

ComponentPhysics::~ComponentPhysics() {

}

IComponent* ComponentPhysics::Clone() {
	return new ComponentPhysics(_gravityVal);
}

int ComponentPhysics::ComponentType() const {
	return _componentType;
}

void ComponentPhysics::Message(IMessage* message) {
	// nothing to do
}

void ComponentPhysics::SetGravity(float value) {
	_gravityVal = value;
}

float ComponentPhysics::GetGravity() const {
	return _gravityVal;
}

void ComponentPhysics::SetIsGravityAffected(bool isAffected) {
	_isGravityAffected = isAffected;
}

bool ComponentPhysics::IsGravityAffected() const {
	return _isGravityAffected;
}

void ComponentPhysics::SetAcceleration(float x, float y, float z) {
	_acceleration = vec3(x, y, z);
}

const vec3& ComponentPhysics::GetAcceleration() {
	return _acceleration;
}

void ComponentPhysics::SetVelocity(float x, float y, float z) {
	_velocity = vec3(x, y, z);
}

const vec3& ComponentPhysics::GetVelocity() {
	return _velocity;
}