#pragma once

#include "Interfaces/IComponent.h"
#include "Managers/ComponentManager.h"

#include "GLM/glm/vec3.hpp"

using namespace EngineECS;
using glm::vec3;

class ComponentRigidbody : public IComponent {
private:
	bool _isKinematic;
	bool _isGravityAffected;
	float _gravityVal;
	float _mass;
	float _frictionCoeff;
	vec3 _netForce;
	vec3 _acceleration;
	vec3 _velocity;

public:
	ComponentRigidbody(float gravity);
	~ComponentRigidbody();

	IComponent* Clone();

	int ComponentType() const;
	void Message(IMessage* message);

	void SetIsKinematic(const bool isKinematic) { _isKinematic = isKinematic; }
	bool IsKinematic() const { return _isKinematic; }

	void SetGravity(const float value) { _gravityVal = value; }
	float GetGravity() const { return _gravityVal; }

	void SetIsGravityAffected(const bool isAffected) { _isGravityAffected = isAffected; }
	bool IsGravityAffected() const { return _isGravityAffected; }

	void SetMass(const float mass) { _mass = mass; }
	float GetMass() const { return _mass; }

	void SetFrictionCoefficient(const float friction) { _frictionCoeff = friction; }
	float GetFrictionCoefficient() const { return _frictionCoeff; }

	void SetForce(const vec3& force) { _netForce = force; }
	void AddForce(const vec3& force) { _netForce += force; }
	const vec3& GetNetForce() const { return _netForce; }

	void SetAcceleration(const float x, const float y, const float z) { _acceleration = vec3(x, y, z); }
	const vec3& GetAcceleration() const { return _acceleration; }

	void SetVelocity(const float x, const float y, const float z) { _velocity = vec3(x, y, z); }
	const vec3& GetVelocity() const { return _velocity; }

};