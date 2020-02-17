#pragma once
#include "Interfaces/ICollisionResponder.h"
#include <stdlib.h>
#include <string>
#include <Tools/Logger.h>

#include "Implementations/CollisionManifold.h"
#include "Components/ComponentScore.h"
#include "Managers/EntityManager.h"

class CollisionResponder : public ICollisionResponder {
private:

public:
	CollisionResponder();
	CollisionResponder(const CollisionResponder& rhs) = delete;
	~CollisionResponder();
	CollisionResponder& operator=(const CollisionResponder& rhs) = delete;

	void HandleCollisions(const vector<ICollisionManifold*>& manifoldList);

	void HandlePlayerItem(Entity* player, Entity* item);
};