#pragma once

#include "GLM/glm\vec3.hpp"
#include "GLM/glm\vec4.hpp"
#include "GLM/glm\mat4x4.hpp"

#include "GLM/glm\gtc\matrix_transform.hpp"

#include "Interfaces/IComponent.h"
#include "Interfaces/IMessage.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

namespace EngineECS {
	class ComponentTransform : public IComponent {
	private:
		bool _dirty;

		vec4 _position;
		vec3 _rotation;
		vec3 _scale;

		mat4 _mTransform;
		mat4 _mRotation;
		mat4 _mScale;

	public:
		ComponentTransform();
		ComponentTransform(float x, float y, float z);
		ComponentTransform(const vec3& position, const vec3& scale, const vec3& rotation);
		ComponentTransform(float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, float xScale, float yScale, float zScale);
		ComponentTransform(const ComponentTransform& rhs);
		~ComponentTransform();
		ComponentTransform operator=(const ComponentTransform& rhs);
		ComponentTransform* Clone();

		int ComponentType() const;
		void Message(IMessage* message);

		const vec4& GetPosition() const					{ return _position;	}
		void SetPosition(const vec4& pos)				{ _position = pos; Clean(); }
		void SetPosition(float x, float y, float z)		{ SetPosition(vec4(x, y, z, 1)); }

		const vec3& GetRotation() const					{ return _rotation; }
		void SetRotation(const vec3& rot)				{ _rotation = rot; Clean(); }
		void SetRotation(float x, float y, float z)		{ SetRotation(vec3(x, y, z)); }

		const vec3& GetScale() const					{ return _scale; }
		void SetScale(const vec3& scale)				{ _scale = scale; Clean(); }
		void SetScale(float a)							{ SetScale(vec3(a, a, a)); }
		void SetScale(float x, float y, float z)		{ SetScale(vec3(x, y, z)); }

		void Clean();

		const mat4& GetMatrixTransform() const			{ return _mTransform; }
		const mat4& GetMatrixRotation() const			{ return _mRotation; }
		const mat4& GetMatrixScale() const				{ return _mScale; }
		const mat4 GetMatrix() const					{ return (_mTransform * _mScale * _mRotation); }
	};
}