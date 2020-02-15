#pragma once
#include "Interfaces/ICollisionDetector.h"

#include <stdlib.h>

#include "Components/ComponentTransform.h"
#include "Components/ComponentCollider.h"
#include "Components/ComponentBoxCollider.h"
#include "Components/ComponentSphereCollider.h"
#include "Implementations/CollisionManifold.h"

class CollisionDetector : public ICollisionDetector {
private:
	ICollisionManifold* CheckBoxBox(Entity* entity1, Entity* entity2);
	ICollisionManifold* CheckSphereSphere(Entity* entity1, Entity* entity2);
	ICollisionManifold* CheckBoxSphere(Entity* entity1, Entity* entity2);

public:

	ICollisionManifold* CollisionCheck(Entity* entity1, Entity* entity2);
	vector<ICollisionManifold*>* CollisionCheck(vector<Entity*>* entityList);
};