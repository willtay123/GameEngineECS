#pragma once
#include "Components/ComponentCollider.h"

#include <glm/vec4.hpp>
#include "Managers/ComponentManager.h"

using glm::vec4;

class ComponentBoxCollider : public ComponentCollider {
private:
	vec4 _centreOffset;
	float _size[3];

public:
	ComponentBoxCollider(float xOff, float yOff, float zOff, float xSize, float ySize, float zSize);
	ComponentBoxCollider(const ComponentBoxCollider& rhs);
	~ComponentBoxCollider();
	ComponentBoxCollider& operator=(const ComponentBoxCollider& rhs);

	IComponent* Clone();

	void Message(IMessage* message);

	void SetCentreOffset(const vec4& rhs);
	const vec4& GetCentreOffset() const;

	void SetSize(float x, float y, float z);
	const float* GetSize() const;
};