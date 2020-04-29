#pragma once
#include "Interfaces/ICollisionDetector.h"

#include <stdlib.h>

#include "Managers/ComponentManager.h"
#include "DataStructs/EntityList.h"
#include "Components/ComponentTransform.h"
#include "Components/ComponentCollider.h"
#include "Components/ComponentBoxCollider.h"
#include "Components/ComponentSphereCollider.h"
#include "Implementations/CollisionManifold.h"

class CollisionDetector : public ICollisionDetector {
private:
	ICollisionManifold* CheckSphereSphere(const Entity& entity1, const Entity& entity2);
	ICollisionManifold* CheckBoxSphere(const Entity& entity1, const Entity& entity2);

public:
	~CollisionDetector();

	ICollisionManifold* DetectCollision(const Entity& entity1, const Entity& entity2);
	void DetectCollisions(const shared_ptr<const EntityList> entityList, vector<ICollisionManifold*>& collisions) override;
};