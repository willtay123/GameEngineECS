#pragma once

#include <GLM/glm/mat4x4.hpp>

#include <vector>

#include "Objects\Camera.h"
#include "Objects\Entity.h"

using std::vector;
using glm::mat4;

namespace EngineECS {
	class IRenderer {
	public:
		virtual bool Initialise() = 0;
		virtual void Draw(const Camera* camera, const Entity* entity) = 0;
		virtual void Draw(const Camera* camera, const vector<Entity*>* entityList) = 0;

		virtual void StartUpdate() = 0;
		virtual void EndUpdate() = 0;

		virtual void StartRender() = 0;
		virtual void EndRender() = 0;

		virtual void Unload() = 0;
	};
}