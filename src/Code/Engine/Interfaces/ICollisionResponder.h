#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Objects/Entity.h"
#include "Interfaces/ICollisionManifold.h"

using std::vector;
using glm::vec3;
using glm::vec4;


class ICollisionResponder {
private:

public:
	virtual void HandleCollisions(const vector<ICollisionManifold*>* manifoldList) = 0;
};