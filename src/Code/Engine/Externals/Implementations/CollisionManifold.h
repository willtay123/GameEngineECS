#pragma once
#include "Interfaces/ICollisionManifold.h"

#include "Objects/Entity.h"

class CollisionManifold : public ICollisionManifold {
private:

public:
	CollisionManifold(Entity* entity1, Entity* entity2);
	CollisionManifold(const CollisionManifold& rhs);
	~CollisionManifold();
	CollisionManifold& operator=(const CollisionManifold& rhs);

	Entity* GetEntity1() const;
	Entity* GetEntity2() const;
};