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
		static CollisionManager* Instance;

		ICollisionDetector* _collisionDetector;
		ICollisionResponder* _collisionResponder;
		vector<ICollisionManifold*> _collisions;

		CollisionManager();

	public:
		~CollisionManager();
		static CollisionManager& GetInstance();

		void SetCollisionDetector(ICollisionDetector* detector);
		void SetCollisionResponder(ICollisionResponder* responder);

		void DetectCollision(const Entity& entity1, const Entity& entity2);
		void DetectCollisions(const vector<Entity*>& entityList);

		void HandleCollisions();
		void ClearCollisions();
	};
}