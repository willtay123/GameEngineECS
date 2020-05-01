#pragma once
#include "CollisionResponder.h"
#include <Components\ComponentTransform.h>
#include <Components\ComponentRigidbody.h>



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
		HandleSphereSphere(entity1, entity2);
	}
}

void CollisionResponder::HandleSphereSphere(shared_ptr<Entity> sphere1, shared_ptr<Entity> sphere2) {
	// If isKinesmatic, bounce the other

	int transformID = ComponentManager::GetInstance().GetIDByType(typeid(ComponentTransform));
	int rigidbodyID = ComponentManager::GetInstance().GetIDByType(typeid(ComponentRigidbody));

	ComponentTransform* transform1 = (ComponentTransform*)sphere1->GetComponent(transformID);
	ComponentRigidbody* rigidbody1 = (ComponentRigidbody*)sphere1->GetComponent(rigidbodyID);
	ComponentTransform* transform2 = (ComponentTransform*)sphere2->GetComponent(transformID);
	ComponentRigidbody* rigidbody2 = (ComponentRigidbody*)sphere2->GetComponent(rigidbodyID);

	if (transform1 && transform2 && rigidbody1 && rigidbody2) {
		float scalar = 1.0f;

		vec4 centre1 = transform1->GetPosition();
		vec4 centre2 = transform2->GetPosition();

		// 1->2
		vec4 distance = centre2 - centre1;
		vec4 direction = glm::normalize(distance);
		vec4 thrust = direction * scalar;

		rigidbody2->AddForce(vec3(thrust.x, thrust.y, thrust.z));
		rigidbody1->AddForce(vec3(-thrust.x, -thrust.y, -thrust.z));
		//rigidbody1->SetVelocity(thrust.x, thrust.y, thrust.z);
		//rigidbody2->SetVelocity(-thrust.x, -thrust.y, -thrust.z);
		//rigidbody1->SetVelocity(0,0,0);
		//rigidbody2->SetVelocity(0,0,0);
	}
}