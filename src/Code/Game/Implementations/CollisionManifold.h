#pragma once
#include "Interfaces/ICollisionManifold.h"

using namespace EngineECS;
#include "Objects/Entity.h"

class CollisionManifold : public ICollisionManifold {
private:

public:

	CollisionManifold(shared_ptr<Entity> entity1, shared_ptr<Entity> entity2);
	CollisionManifold(const CollisionManifold& rhs);
	~CollisionManifold();
	CollisionManifold& operator=(const CollisionManifold& rhs);

	shared_ptr<Entity> GetEntity1() const;
	shared_ptr<Entity> GetEntity2() const;
};