#include "ComponentTransform.h"

using namespace EngineECS;

ComponentTransform::ComponentTransform() :
	_position(0, 0, 0, 1),
	_rotation(0, 0, 0),
	_scale(1, 1, 1) {
	//_componentType = ComponentManager::GenerateIDByType(this);
	_componentType = ComponentManager::GetInstance().GetIDByType(typeid(ComponentTransform));
	Clean();
}

ComponentTransform::ComponentTransform(float x, float y, float z) :
	_position(x, y, z, 1),
	_rotation(0, 0, 0),
	_scale(1, 1, 1) {
	//_componentType = ComponentManager::GenerateIDByType(this);
	_componentType = ComponentManager::GetInstance().GetIDByType(typeid(ComponentTransform));
	Clean();
}

ComponentTransform::ComponentTransform(const vec3& position, const vec3& scale, const vec3& rotation) :
	_position(position.x, position.y, position.z, 1),
	_scale(scale),
	_rotation(rotation) {
	_componentType = ComponentManager::GetInstance().GetIDByType(typeid(ComponentTransform));
	Clean();
}

ComponentTransform::ComponentTransform(float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, float xScale, float yScale, float zScale) :
	_position(xPos, yPos, zPos, 1),
	_rotation(xRot, yRot, zRot),
	_scale(xScale, yScale, zScale) {
	//_componentType = ComponentManager::GenerateIDByType(this);
	_componentType = ComponentManager::GetInstance().GetIDByType(typeid(ComponentTransform));
	Clean();
}

ComponentTransform::ComponentTransform(const ComponentTransform& rhs) :
	_dirty(rhs._dirty),
	_position(rhs._position),
	_rotation(rhs._rotation),
	_scale(rhs._scale),
	_mTransform(rhs._mTransform),
	_mRotation(rhs._mRotation),
	_mScale(rhs._mScale) {

}

ComponentTransform::~ComponentTransform() {

}

ComponentTransform ComponentTransform::operator=(const ComponentTransform& rhs) {
	if (this != &rhs) {
		_componentType = rhs._componentType;
		_dirty = rhs._dirty;
		_position = rhs._position;
		_rotation = rhs._rotation;
		_scale = rhs._scale;
		_mTransform = rhs._mTransform;
		_mRotation = rhs._mRotation;
		_mScale = rhs._mScale;
	}
	return *this;
}

ComponentTransform* ComponentTransform::Clone() {
	ComponentTransform* clone = new ComponentTransform(*this);
	return clone;
}

int ComponentTransform::ComponentType() const {
	return _componentType;
}

void ComponentTransform::Message(IMessage* message) {

}

void ComponentTransform::Clean() {
	// Transform
	_mTransform = glm::translate(glm::mat4(1.0f), glm::vec3(_position.x, _position.y, _position.z));

	// Rotation
	mat4 rotX = glm::rotate(glm::mat4(1.0f), _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	mat4 rotY = glm::rotate(glm::mat4(1.0f), _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	mat4 rotZ = glm::rotate(glm::mat4(1.0f), _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	_mRotation = rotX * rotY * rotZ;

	// Scale
	_mScale = glm::scale(glm::mat4(1.0f), glm::vec3(_scale.x, _scale.y, _scale.z));

	// Cleaned
	_dirty = false;
}
