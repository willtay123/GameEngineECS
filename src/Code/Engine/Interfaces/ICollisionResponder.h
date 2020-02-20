#pragma once

#include <vector>
#include <GLM/glm/vec3.hpp>
#include <GLM/glm/vec4.hpp>

#include "Objects/Entity.h"
#include "Interfaces/ICollisionManifold.h"

using std::vector;
using glm::vec3;
using glm::vec4;

namespace EngineECS {
	class ICollisionResponder {
	private:

	public:
		virtual ~ICollisionResponder() {}

		virtual void HandleCollisions(const vector<ICollisionManifold*>& manifoldList) = 0;
	};
}