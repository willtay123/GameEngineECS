#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Objects/Entity.h"

using glm::vec3;
using glm::vec4;


class ICollisionManifold {
protected:
	Entity* _entity1;
	Entity* _entity2;
	vec4 _pointOfCollision;

public:

};