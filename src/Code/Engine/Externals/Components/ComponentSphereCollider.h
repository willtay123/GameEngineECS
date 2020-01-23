#pragma once
#include "Components/ComponentCollider.h"

#include <glm/vec4.hpp>
#include "Managers/ComponentManager.h"

using glm::vec4;

class ComponentSphereCollider : public ComponentCollider {
private:
	vec4 _centreOffset;
	float _radius;

public:
	ComponentSphereCollider(float xOff, float yOff, float zOff, float radius);
	ComponentSphereCollider(const ComponentSphereCollider& rhs);
	~ComponentSphereCollider();
	ComponentSphereCollider& operator=(const ComponentSphereCollider& rhs);

	IComponent* Clone();

	int ComponentType() const;
	void Message(IMessage* message);

	void SetCentreOffset(const vec4& offset);
	const vec4& GetCentreOffset() const;

	void SetRadius(float radius);
	float GetRadius() const;
};