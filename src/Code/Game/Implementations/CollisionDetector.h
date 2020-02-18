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
	ICollisionManifold* CheckBoxBox(const Entity& entity1, const Entity& entity2);
	ICollisionManifold* CheckSphereSphere(const Entity& entity1, const Entity& entity2);
	ICollisionManifold* CheckBoxSphere(const Entity& entity1, const Entity& entity2);

public:

	ICollisionManifold* CollisionCheck(const Entity& entity1, const Entity& entity2);
	vector<ICollisionManifold*>* CollisionCheck(const std::shared_ptr<EntityList> entityList);
};