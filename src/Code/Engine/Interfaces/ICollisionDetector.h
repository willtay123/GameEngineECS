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
		virtual ICollisionManifold* CollisionCheck(const Entity& entity1, const Entity& entity2) = 0;
		virtual vector<ICollisionManifold*>* CollisionCheck(const std::shared_ptr<EntityList> entityList) = 0; // TODO: change to use out parameter
	};
}