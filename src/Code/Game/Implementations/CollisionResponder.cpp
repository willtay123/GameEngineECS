#pragma once
#include "CollisionResponder.h"



CollisionResponder::CollisionResponder() {

}

CollisionResponder::~CollisionResponder() {

}

void CollisionResponder::HandleCollisions(const vector<ICollisionManifold*>& manifoldList) {
	for (ICollisionManifold* iManifold : manifoldList) {
		//handle collisions

		CollisionManifold* manifold = (CollisionManifold*)iManifold;

		shared_ptr<Entity> entity1 = manifold->GetEntity1();
		shared_ptr<Entity> entity2 = manifold->GetEntity2();

		// Sphere Sphere
		if (entity1->GetID() == "sphere" && entity2->GetID() == "sphere") {
			HandleSphereSphere(entity1, entity2);
		}
	}
}

void CollisionResponder::HandleSphereSphere(shared_ptr<Entity> sphere1, shared_ptr<Entity> sphere2) {

}