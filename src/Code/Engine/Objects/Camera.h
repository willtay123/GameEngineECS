#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <GLM/glm/glm.hpp>
#include <GLM/glm/gtx/transform.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::lookAt;

namespace EngineECS {
	class Camera {
	private:
		bool _isDirty;
		vec3* _position;
		vec3* _lookPosition;
		vec3* _up;
		mat4* _view;
		mat4* _projection;

	public:
		Camera();
		Camera(const Camera& rhs) = delete;
		~Camera();
		Camera& operator=(const Camera& rhs) = delete;

		void SetProjection(mat4* proj);

		const vec3* GetPosition() const;
		const vec3* GetLookPosition() const;
		const vec3* GetUp() const;
		const mat4* GetView() const;
		const mat4* GetProjection() const;

		void MoveTo(vec3* position);
		void MoveBy(vec3* translation);

		void LookPosition(vec3* lookPosition);
		void TransformLookPosition(mat4* transform);

		void SetUp(vec3* up);
		void TransformUp(mat4* transform);

		void Update(double deltaTime);
	};
}