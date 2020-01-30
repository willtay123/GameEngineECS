#pragma once

#include <vector>
#include "GLM/glm/vec3.hpp"
#include "GLM/glm/vec4.hpp"

#include "Objects/Entity.h"
#include "Interfaces/ICollisionManifold.h"
#include "Interfaces/ICollisionDetector.h"
#include "Interfaces/ICollisionResponder.h"

using std::vector;
using glm::vec3;
using glm::vec4;

namespace EngineECS {
	class CollisionManager {
	private:
		static ICollisionDetector* _collisionDetector;
		static ICollisionResponder* _collisionResponder;
		static vector<ICollisionManifold*>* _collisions;

	public:
		static void Initialise(ICollisionDetector* detector, ICollisionResponder* responder);

		static void DetectCollision(Entity* entity1, Entity* entity2);
		static void DetectCollisions(vector<Entity*>* entityList);

		static void HandleCollisions();
		static void ClearCollisions();

		static void End();
	};
}