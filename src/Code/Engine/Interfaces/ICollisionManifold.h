#pragma once

#include <GLM/glm/vec3.hpp>
#include <GLM/glm/vec4.hpp>

#include "Objects/Entity.h"
#include "CleverPointers.h"

using glm::vec3;
using glm::vec4;

namespace EngineECS {
	class ICollisionManifold {
	protected:
		shared_ptr<Entity> _entity1;
		shared_ptr<Entity> _entity2;

	public:
		virtual ~ICollisionManifold() {}
	};
}