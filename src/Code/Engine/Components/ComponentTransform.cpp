#include "ComponentTransform.h"

using namespace EngineECS;

ComponentTransform::ComponentTransform() :
	_pos(0, 0, 0, 1),
	_rot(0, 0, 0),
	_scale(1, 1, 1) {
	//_componentType = ComponentManager::GenerateIDByType(this);
	_componentType = ComponentManager::GetInstance().GetIDByType(typeid(ComponentTransform));
	Clean();
}

ComponentTransform::ComponentTransform(float x, float y, float z) :
	_pos(x, y, z, 1),
	_rot(0, 0, 0),
	_scale(1, 1, 1) {
	//_componentType = ComponentManager::GenerateIDByType(this);
	_componentType = ComponentManager::GetInstance().GetIDByType(typeid(ComponentTransform));
	Clean();
}

ComponentTransform::ComponentTransform(float xPos, float yPos, float zPos, float xRot, float yRot, float zRot) :
	_pos(xPos, yPos, zPos, 1),
	_rot(xRot, yRot, zRot),
	_scale(1, 1, 1) {
	//_componentType = ComponentManager::GenerateIDByType(this);
	_componentType = ComponentManager::GetInstance().GetIDByType(typeid(ComponentTransform));
	Clean();
}

ComponentTransform::ComponentTransform(float xPos, float yPos, float zPos, float scale) :
	_pos(xPos, yPos, zPos, 1),
	_rot(0, 0, 0),
	_scale(scale) {
	//_componentType = ComponentManager::GenerateIDByType(this);
	_componentType = ComponentManager::GetInstance().GetIDByType(typeid(ComponentTransform));
	Clean();
}

ComponentTransform::ComponentTransform(float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, float xScale, float yScale, float zScale) :
	_pos(xPos, yPos, zPos, 1),
	_rot(xRot, yRot, zRot),
	_scale(xScale, yScale, zScale) {
	//_componentType = ComponentManager::GenerateIDByType(this);
	_componentType = ComponentManager::GetInstance().GetIDByType(typeid(ComponentTransform));
	Clean();
}

ComponentTransform::ComponentTransform(const ComponentTransform& rhs) :
	_dirty(rhs._dirty),
	_pos(rhs._pos),
	_rot(rhs._rot),
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
		_pos = rhs._pos;
		_rot = rhs._rot;
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

const vec4& ComponentTransform::GetPosition() const {
	return _pos;
}
void ComponentTransform::SetPosition(vec4* pos) {
	_pos = *pos;
	Clean();
}
void ComponentTransform::SetPosition(float x, float y, float z) {
	_pos.x = x;
	_pos.y = y;
	_pos.z = z;
	Clean();
}

const vec3& ComponentTransform::GetRotation() const {
	return _rot;
}
void ComponentTransform::SetRotation(vec3* rot) {
	_rot = *rot;
	Clean();
}
void ComponentTransform::SetRotation(float x, float y, float z) {
	_rot.x = x;
	_rot.y = y;
	_rot.z = z;
	Clean();
}

const vec3& ComponentTransform::GetScale() const {
	return _scale;
}
void ComponentTransform::SetScale(vec3* scale) {
	_scale = *scale;
	Clean();
}
void ComponentTransform::SetScale(float a) {
	_scale.x = a;
	_scale.y = a;
	_scale.z = a;
	Clean();
}
void ComponentTransform::SetScale(float x, float y, float z) {
	_scale.x = x;
	_scale.y = y;
	_scale.z = z;
	Clean();
}

void ComponentTransform::Clean() {
	// Transform
	_mTransform = glm::translate(glm::mat4(1.0f), glm::vec3(_pos.x, _pos.y, _pos.z));

	// Rotation
	mat4 rotX = glm::rotate(glm::mat4(1.0f), _rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
	mat4 rotY = glm::rotate(glm::mat4(1.0f), _rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
	mat4 rotZ = glm::rotate(glm::mat4(1.0f), _rot.z, glm::vec3(0.0f, 0.0f, 1.0f));
	_mRotation = rotX * rotY * rotZ;

	// Scale
	_mScale = glm::scale(glm::mat4(1.0f), glm::vec3(_scale.x, _scale.y, _scale.z));

	// Cleaned
	_dirty = false;
}

const mat4& ComponentTransform::GetMatrixTransform() const {
	return _mTransform;
}

const mat4& ComponentTransform::GetMatrixRotation() const {
	return _mRotation;
}

const mat4& ComponentTransform::GetMatrixScale() const {
	return _mScale;
}

const mat4 ComponentTransform::GetMatrix() const {
	return (_mTransform * _mScale * _mRotation);
}