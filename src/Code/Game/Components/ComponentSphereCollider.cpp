#include "ComponentSphereCollider.h"



ComponentSphereCollider::ComponentSphereCollider(float xOff, float yOff, float zOff, float radius) : ComponentCollider(true) {
	_componentType = ComponentManager::GenerateIDByString("collider");
	_colliderType = string("Sphere");
	_centreOffset = vec4(xOff, yOff, zOff, 0);
	_radius = radius;
}

ComponentSphereCollider::ComponentSphereCollider(const ComponentSphereCollider& rhs) {
	_enabled = rhs._enabled;
	_colliderType = rhs._colliderType;
	_centreOffset = rhs._centreOffset;
	_radius = rhs._radius;
}

ComponentSphereCollider::~ComponentSphereCollider() {

}

ComponentSphereCollider& ComponentSphereCollider::operator=(const ComponentSphereCollider& rhs) {
	if (this != &rhs) {
		_enabled = rhs._enabled;
		_colliderType = rhs._colliderType;
		_centreOffset = rhs._centreOffset;
		_radius = rhs._radius;
	}
	return *this;
}

IComponent* ComponentSphereCollider::Clone() {
	// return copy of this
	return NULL;
}

int ComponentSphereCollider::ComponentType() const {
	return _componentType;
}

void ComponentSphereCollider::Message(IMessage* message) {

}

void ComponentSphereCollider::SetCentreOffset(const vec4& offset) {
	_centreOffset = offset;
}

const vec4& ComponentSphereCollider::GetCentreOffset() const {
	return _centreOffset;
}

void ComponentSphereCollider::SetRadius(float radius) {
	_radius = radius;
}

float ComponentSphereCollider::GetRadius() const {
	return _radius;
}