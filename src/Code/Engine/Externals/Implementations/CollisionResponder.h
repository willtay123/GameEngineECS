#pragma once
#include "Interfaces/ICollisionResponder.h"

#include <iostream>
#include <stdlib.h>
#include <string>

#include "Externals/Implementations/CollisionManifold.h"
#include "Externals/Components/ComponentScore.h"
#include "Managers/EntityManager.h"

using std::cout;
using std::endl;


class CollisionResponder : public ICollisionResponder {
private:

public:
	CollisionResponder();
	CollisionResponder(const CollisionResponder& rhs) = delete;
	~CollisionResponder();
	CollisionResponder& operator=(const CollisionResponder& rhs) = delete;

	void HandleCollisions(const vector<ICollisionManifold*>* manifoldList);

	void HandlePlayerItem(Entity* player, Entity* item);
};