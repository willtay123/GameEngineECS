#include "Camera.h"

using namespace EngineECS;

Camera::Camera() {
	_isDirty = false;
	_position = new vec3(4, 3, 3);
	_lookPosition = new vec3(0, 0, 0);
	_up = new vec3(0, 1, 0);
	_view = new mat4(1.0f);
	_projection = new mat4(1.0f);

	// View
	*_view = lookAt(
		*_position,
		*_lookPosition,
		*_up
	);

	// Projection
	*_projection = glm::perspective(
		(float)glm::radians(80.0f),
		1280.0f / 780.0f,
		1.0f,
		50.0f
	);
}

Camera::~Camera() {
	delete _position;
	delete _lookPosition;
	delete _up;
	delete _view;
}

void Camera::SetProjection(mat4* proj) {
	*_projection = *proj;
}

const vec3* Camera::GetPosition() const {
	return _position;
}

const vec3* Camera::GetLookPosition() const {
	return _lookPosition;
}

const vec3* Camera::GetUp() const {
	return _up;
}

const mat4* Camera::GetView() const {
	return _view;
}

const mat4* Camera::GetProjection() const {
	return _projection;
}

void Camera::MoveTo(vec3* position) {
	_isDirty = true;

	*_position = *position;
}

void Camera::MoveBy(vec3* position) {
	_isDirty = true;

	*_position += *position;
}

void Camera::LookPosition(vec3* lookPosition) {
	_isDirty = true;

	*_lookPosition = *lookPosition;
}

void Camera::TransformLookPosition(mat4* transform) {
	_isDirty = true;

	//get _lookPosition as vec4
	vec4 lookPosAs4 = vec4(
		_lookPosition->x,
		_lookPosition->y,
		_lookPosition->z,
		1
	);

	//transform _lookPosition
	lookPosAs4 = *transform * lookPosAs4;

	//save _lookPosition as vec3
	_lookPosition->x = lookPosAs4.x;
	_lookPosition->y = lookPosAs4.y;
	_lookPosition->z = lookPosAs4.z;
}

void Camera::SetUp(vec3* up) {
	_isDirty = true;
	*_up = *up;
}

void Camera::TransformUp(mat4* transform) {
	_isDirty = true;

	//get _up as vec4
	vec4 upAs4 = vec4(
		_up->x,
		_up->y,
		_up->z,
		1
	);

	//transform _up
	upAs4 = *transform * upAs4;

	//save _up as vec3
	_up->x = upAs4.x;
	_up->y = upAs4.y;
	_up->z = upAs4.z;
}

void Camera::Update(double deltaTime) {
	if (_isDirty) {
		*_view = lookAt(
			*_position,
			*_lookPosition,
			*_up
		);
		_isDirty = false;
	}
}