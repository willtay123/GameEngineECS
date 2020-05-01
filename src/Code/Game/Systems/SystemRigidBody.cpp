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

			// Position
			vec4 newPos = vec4(
				position.x + (vel.x * dt),
				position.y + (vel.y * dt),
				position.z + (vel.z * dt),
				1
			);

			// If new position is in floor, bounce
			if (newPos.y <= 0) {
				float localDT = dt;

				// Solve quadratic
				float a = -gravity;
				float b = vel.y;
				float c = position.y;
				float s = b * b - 4.0f * a * c;
				s = (s > 0.0f ? sqrt(s) : 0.0f);
				float t1 = (-b + s) / (2.0f * a);
				float t2 = (-b - s) / (2.0f * a);
				float collisionT = (t1 > t2 ? t1 : t2);

				// Check --- height should be zero
				newPos.y = position.y + vel.y * collisionT + 0.5f * gravity * collisionT * collisionT;

				// At collision
				vel.y = vel.y + gravity * collisionT;
				vel.y *= -1;

				// Bounce
				localDT -= collisionT;
				newPos.y = vel.y * localDT + 0.5f * gravity * localDT * localDT;
			}

			// Velocity
			vel += (acc * dt);

			// Set values
			rigidbody->SetAcceleration(0, 0, 0);
			rigidbody->SetVelocity(vel.x, vel.y, vel.z);

			transfComponent->SetPosition(newPos);
		}
	}
}