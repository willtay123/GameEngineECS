#pragma once
#include "Interfaces/ICollisionDetector.h"

#include <iostream>
#include <stdlib.h>

#include "Components/ComponentTransform.h"
#include "Components/ComponentCollider.h"
#include "Externals/Components/ComponentBoxCollider.h"
#include "Externals/Components/ComponentSphereCollider.h"
#include "Externals/Implementations/CollisionManifold.h"

using std::cout;
using std::endl;

class CollisionDetector : public ICollisionDetector {
private:
	ICollisionManifold* CheckBoxBox(Entity* entity1, Entity* entity2);
	ICollisionManifold* CheckSphereSphere(Entity* entity1, Entity* entity2);
	ICollisionManifold* CheckBoxSphere(Entity* entity1, Entity* entity2);

public:

	ICollisionManifold* CollisionCheck(Entity* entity1, Entity* entity2);
	vector<ICollisionManifold*>* CollisionCheck(vector<Entity*>* entityList);
};