#pragma once

#include "Interfaces/IComponent.h"
#include "Managers/ComponentManager.h"

#include "GLM/glm/vec3.hpp"

using namespace EngineECS;
using glm::vec3;

class ComponentPhysics : public IComponent {
private:
	bool _isGravityAffected;
	float _gravityVal;
	vec3 _acceleration;
	vec3 _velocity;

public:
	ComponentPhysics(float gravity);
	~ComponentPhysics();

	IComponent* Clone();

	int ComponentType() const;
	void Message(IMessage* message);

	void SetGravity(float value);
	float GetGravity() const;

	void SetIsGravityAffected(bool isAffected);
	bool IsGravityAffected() const;
	
	void SetAcceleration(float x, float y, float z);
	const vec3& GetAcceleration();

	void SetVelocity(float x, float y, float z);
	const vec3& GetVelocity();
};