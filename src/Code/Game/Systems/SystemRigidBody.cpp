#include "SystemRigidBody.h"



SystemRigidBody::SystemRigidBody() :
	_name("Physics System") {
}

SystemRigidBody::~SystemRigidBody() {

}

const string& SystemRigidBody::GetName() {
	return _name;
}

void SystemRigidBody::OnAction(double deltaTime) {
	float dt = static_cast<float>(deltaTime);
	int transformID = ComponentManager::GetInstance().GetIDByType(typeid(ComponentTransform));
	int physicsID = ComponentManager::GetInstance().GetIDByType(typeid(ComponentRigidbody));

	shared_ptr<EntityList> entityList = EntityManager::GetInstance().GetEntitiesEditable();

	for (int i = 0; i < entityList->size(); i++) {
		ComponentTransform* transfComponent = static_cast<ComponentTransform*>((*entityList)[i]->GetComponentEditable(transformID));
		ComponentRigidbody* rigidbody = static_cast<ComponentRigidbody*>((*entityList)[i]->GetComponentEditable(physicsID));

		if (transfComponent &&
			rigidbody) {

			// Dont move if kinematic
			if (rigidbody->IsKinematic()) {
				continue;
			}

			// Fetch values
			float gravity = rigidbody->GetGravity();
			float mass = rigidbody->GetMass();
			float frictionCoeff = rigidbody->GetFrictionCoefficient();
			vec3 netForce = rigidbody->GetNetForce();
			vec3 vel = rigidbody->GetVelocity();
			const vec4 position = transfComponent->GetPosition();


			// --Calculate physics
			// Acc
			vec3 acc = netForce / mass;

			// Gravity
			if (rigidbody->IsGravityAffected()) {
				acc.y -= gravity;
			}

			// Velocity
			vel += (acc * dt);
			
			// Friction
			float frictionValue = 0.97f; // frictionCoeff * mass* gravity;
			vel *= frictionValue;

			// Position
			vec4 newPos = vec4(
				position.x + (vel.x * dt),
				position.y + (vel.y * dt),
				position.z + (vel.z * dt),
				1
			);

			// Set values
			rigidbody->SetAcceleration(0, 0, 0);
			rigidbody->SetVelocity(vel.x, vel.y, vel.z);

			transfComponent->SetPosition(newPos);
		}
	}
}