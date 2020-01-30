#include "ComponentBoxCollider.h"



ComponentBoxCollider::ComponentBoxCollider(float xOff, float yOff, float zOff, float xSize, float ySize, float zSize) : 
	ComponentCollider(true) {
	_componentType = ComponentManager::GenerateIDByString("BoxCollider");
	_colliderType = string("Box");
	_centreOffset = vec4(xOff, yOff, zOff, 0);
	_size[0] = xSize;
	_size[1] = ySize;
	_size[2] = zSize;
}

ComponentBoxCollider::ComponentBoxCollider(const ComponentBoxCollider& rhs) {
	_enabled = rhs._enabled;
	_colliderType = rhs._colliderType;
	_centreOffset = rhs._centreOffset;
	for (int i = 0; i < 3; i++) {
		_size[i] = rhs._size[i];
	}
}

ComponentBoxCollider::~ComponentBoxCollider() {

}

ComponentBoxCollider& ComponentBoxCollider::operator=(const ComponentBoxCollider& rhs) {
	if (this != &rhs) {
		_enabled = rhs._enabled;
		_colliderType = rhs._colliderType;
		_centreOffset = rhs._centreOffset;
		for (int i = 0; i < 3; i++) {
			_size[i] = rhs._size[i];
		}
	}
	return *this;
}

IComponent* ComponentBoxCollider::Clone() {
	return NULL;
}

void ComponentBoxCollider::Message(IMessage* message) {

}

void ComponentBoxCollider::SetCentreOffset(const vec4& offset) {
	_centreOffset = offset;
}

const vec4& ComponentBoxCollider::GetCentreOffset() const {
	return _centreOffset;
}

void ComponentBoxCollider::SetSize(float x, float y, float z) {
	_size[0] = x;
	_size[1] = y;
	_size[2] = z;
}

const float* ComponentBoxCollider::GetSize() const {
	return _size;
}