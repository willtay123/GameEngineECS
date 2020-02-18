#include "Camera.h"

using namespace EngineECS;

Camera::Camera() :
	_isDirty(false),
	_position(0,0,0,1),
	_direction(1,0,0,1),
	_up(0,1,0,1),
	_view(1.0f),
	_projection(1.0f) {

	// View
	_view = lookAt(
		vec3(_position),
		vec3(_position + _direction),
		vec3(_up)
	);

	// Projection
	_projection = glm::perspective(
		(float)glm::radians(80.0f),
		1280.0f / 780.0f,
		1.0f,
		50.0f
	);
}

Camera::~Camera() {
}

void Camera::SetProjection(const mat4& proj) {
	_projection = proj;
}

void Camera::SetPosition(const vec3& position) {
	_isDirty = true;
	_position = vec4(position, 1);
}

void Camera::SetDirection(const vec3& direction) {
	_isDirty = true;
	_direction = vec4(glm::normalize(direction), 1);
}

void Camera::SetUp(const vec3& up) {
	_isDirty = true;
	_up = vec4(glm::normalize(up), 1);
}

void Camera::LookAt(const vec3& lookPosition, const vec3& up) {
	_isDirty = true;

	vec3 pos(_position);
	vec3 direction = glm::normalize(lookPosition - pos);

	_direction = vec4(direction, 1);
	_up = vec4(up, 1);
}

void Camera::MoveBy(const vec3& position) {
	_isDirty = true;
	_position += vec4(position, 0);
}

void Camera::TurnOnAxis(const float angleInDeg, const vec3& axis) {
	_isDirty = true;
	float angleInRad = glm::radians(angleInDeg);
	mat4 rotateMat = glm::rotate(angleInRad, axis);

	RotateByMatrix(rotateMat);
}

void Camera::RotateByMatrix(const mat4& matrix) {
	_direction = matrix * _direction;
	_up = matrix * _up;
}

const vec4& Camera::GetPosition() const {
	return _position;
}

const vec4& Camera::GetDirection() const {
	return _direction;
}

const vec4& Camera::GetUp() const {
	return _up;
}

const mat4& Camera::GetView() const {
	return _view;
}

const mat4& Camera::GetProjection() const {
	return _projection;
}

void Camera::Update(double deltaTime) {
	if (_isDirty) {
		_view = lookAt(
			vec3(_position),
			vec3(_position + _direction),
			vec3(_up)
		);
		_isDirty = false;
	}
}