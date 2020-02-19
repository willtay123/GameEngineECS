#pragma once

#include <vector>
#include <GLM/glm/vec3.hpp>
#include <GLM/glm/vec4.hpp>

#include "DataStructs/EntityList.h"
#include "Objects/Entity.h"
#include "Interfaces/ICollisionManifold.h"

using std::vector;
using glm::vec3;
using glm::vec4;

namespace EngineECS {
	class ICollisionDetector {
	private:

	public:
		virtual ~ICollisionDetector() = 0;

		virtual void DetectCollisions(const std::weak_ptr<EntityList> entityList, vector<ICollisionManifold*>& collisions) = 0;
	};
}