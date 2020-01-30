#pragma once

#include "pch.h"
#include <vector>
#include <GLM/glm/vec3.hpp>
#include <GLM/glm/vec4.hpp>

#include "Objects/Entity.h"
#include "Interfaces/ICollisionManifold.h"

using std::vector;
using glm::vec3;
using glm::vec4;

namespace EngineECS {
	class ICollisionDetector {
	private:

	public:
		virtual ICollisionManifold* CollisionCheck(Entity* entity1, Entity* entity2) = 0;
		virtual vector<ICollisionManifold*>* CollisionCheck(vector<Entity*>* entityList) = 0;
	};
}