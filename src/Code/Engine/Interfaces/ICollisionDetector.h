#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Objects/Entity.h"
#include "Interfaces/ICollisionManifold.h"

using std::vector;
using glm::vec3;
using glm::vec4;


class ICollisionDetector {
private:

public:
	virtual ICollisionManifold* CollisionCheck(Entity* entity1, Entity* entity2) = 0;
	virtual vector<ICollisionManifold*>* CollisionCheck(vector<Entity*>* entityList) = 0;
};