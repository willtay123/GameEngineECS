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
		vec4 _position;
		vec4 _direction;
		vec4 _up;

		mat4 _view;
		mat4 _projection;

	public:
		Camera();
		Camera(const Camera& rhs) = delete;
		~Camera();
		Camera& operator=(const Camera& rhs) = delete;

		void SetProjection(const mat4& proj);

		void SetPosition(const vec3& position);
		void SetDirection(const vec3& direction);
		void SetUp(const vec3& up);

		void LookAt(const vec3&lookPosition, const vec3& up);
		void MoveBy(const vec3& translation);
		void TurnOnAxis(const float angleInDeg, const vec3& axis);

		const vec3& GetPosition() const;
		const vec3& GetDirection() const;
		const vec3& GetUp() const;
		const mat4& GetView() const;
		const mat4& GetProjection() const;

		void Update(const double deltaTime);
	};
}