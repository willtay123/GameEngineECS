#include "CollisionDetector.h"



ICollisionManifold* CollisionDetector::CollisionCheck(Entity* entity1, Entity* entity2) {
	// work out collider types, call relevant method
	int colliderID = ComponentManager::GenerateIDByString("collider");
	ComponentCollider* collider1 = (ComponentCollider*)entity1->GetComponentEditable(colliderID);
	ComponentCollider* collider2 = (ComponentCollider*)entity2->GetComponentEditable(colliderID);
	string collider1Type = collider1->GetColliderType();
	string collider2Type = collider2->GetColliderType();

	if (collider1Type == "Box" && collider2Type == "Box") {
		// call Box Box
		return CheckBoxBox(entity1, entity2);
	}

	if (collider1Type == "Sphere" && collider2Type == "Sphere") {
		// Call Sphere Sphere
		return CheckSphereSphere(entity1, entity2);
	}

	if (collider1Type == "Box" && collider2Type == "Sphere" ||
		collider1Type == "Sphere" && collider2Type == "Box") {
		if (collider1Type == "Box") {
			// call Box Sphere
			return CheckBoxSphere(entity1, entity2);
		}
		else {
			// call Sphere Box
			return CheckBoxSphere(entity2, entity1);
		}
	}

	return NULL;
}

vector<ICollisionManifold*>* CollisionDetector::CollisionCheck(vector<Entity*>* entityList) {
	vector<ICollisionManifold*>* manifoldList = new vector<ICollisionManifold*>();
	for (int i = 0; i < (int)(entityList->size()) - 1; i += 1) {
		for (int j = i + 1; j < (int)(entityList->size()); j += 1) {
			Entity* ent1 = (*entityList)[i];
			Entity* ent2 = (*entityList)[j];
			ICollisionManifold* manifold = CollisionCheck(ent1, ent2);
			if (manifold) {
				manifoldList->push_back(manifold);
			}
		}
	}
	return manifoldList;
}

ICollisionManifold* CollisionDetector::CheckBoxBox(Entity* entity1, Entity* entity2) {
	return NULL;
}

ICollisionManifold* CollisionDetector::CheckSphereSphere(Entity* entity1, Entity* entity2) {
	if (entity1 == entity2) {
		return NULL;
	}

	int transformID = ComponentManager::GetIDForString("Transform");
	int sphereID = ComponentManager::GetIDForString("collider");

	ComponentTransform* transform1 = (ComponentTransform*)entity1->GetComponentEditable(transformID);
	ComponentSphereCollider* collider1 = (ComponentSphereCollider*)entity1->GetComponentEditable(sphereID);
	ComponentTransform* transform2 = (ComponentTransform*)entity2->GetComponentEditable(transformID);
	ComponentSphereCollider* collider2 = (ComponentSphereCollider*)entity2->GetComponentEditable(sphereID);

	if (transform1 && collider1 &&
		transform2 && collider2) {
		vec4 collisionCentre1 = *(transform1->GetPosition()) + collider1->GetCentreOffset();
		vec4 collisionCentre2 = *(transform2->GetPosition()) + collider2->GetCentreOffset();
		float radius1 = collider1->GetRadius();
		float radius2 = collider2->GetRadius();
		float radiiSum = radius1 + radius2;

		vec4 dVec = collisionCentre2 - collisionCentre1;
		float distance = std::sqrt(dVec.x * dVec.x + dVec.y * dVec.y + dVec.z * dVec.z);

		//cout << "Position1: " << collisionCentre1.x << " " << collisionCentre1.y << " " << collisionCentre1.z << endl;
		//cout << "Position2: " << collisionCentre2.x << " " << collisionCentre2.y << " " << collisionCentre2.z << endl;
		//cout << "Radius1: " << radius1 << endl;
		//cout << "Radius2: " << radius2 << endl;
		//cout << "Distance: " << distance << endl;

		if (distance < radiiSum) {
			// Collision
			return new CollisionManifold(entity1, entity2);
		}
		else {
			return NULL;
		}
	}

	return NULL;
}

ICollisionManifold* CollisionDetector::CheckBoxSphere(Entity* entity1, Entity* entity2) {
	return NULL;
}