#pragma once
#include "Interfaces/IComponent.h"
#include "glm\vec3.hpp"
#include "glm\vec4.hpp"
#include "glm\mat4x4.hpp"

#include "glm\gtc\matrix_transform.hpp"

using glm::vec3;
using glm::vec4;
using glm::mat4;

class ComponentTransform : public IComponent {
private:
	bool _dirty;

	vec4 _pos;
	vec3 _rot;
	vec3 _scale;

	mat4 _mTransform;
	mat4 _mRotation;
	mat4 _mScale;

public:
	ComponentTransform();
	ComponentTransform(float x, float y, float z);
	ComponentTransform(float xPos, float yPos, float zPos, float xRot, float yRot, float zRot);
	ComponentTransform(float xPos, float yPos, float zPos, float scale);
	ComponentTransform(float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, float xScale, float yScale, float zScale);
	ComponentTransform(const ComponentTransform& rhs);
	~ComponentTransform();
	ComponentTransform operator=(const ComponentTransform& rhs);
	ComponentTransform* Clone();

	int ComponentType() const;
	void Message(IMessage* message);

	const vec4* GetPosition() const;
	void SetPosition(vec4* pos);
	void SetPosition(float x, float y, float z);

	const vec3* GetRotation() const;
	void SetRotation(vec3* rot);
	void SetRotation(float x, float y, float z);

	const vec3* GetScale() const;
	void SetScale(vec3* scale);
	void SetScale(float a);
	void SetScale(float x, float y, float z);

	void Clean();

	const mat4* GetMatrixTransform() const;
	const mat4* GetMatrixRotation() const;
	const mat4* GetMatrixScale() const;
	const mat4 GetMatrix() const;
};