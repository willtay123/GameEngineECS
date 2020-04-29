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
	int transformID = ComponentManager::GetInstance().GetIDByType(typeid(ComponentTransform));
	int physicsID = ComponentManager::GetInstance().GetIDByType(typeid(ComponentRigibody));

	shared_ptr<EntityList> entityList = EntityManager::GetInstance().GetEntitiesEditable();

	for (int i = 0; i < entityList->size(); i++) {
		ComponentTransform* transfComponent = static_cast<ComponentTransform*>((*entityList)[i]->GetComponentEditable(transformID));
		ComponentRigibody* physicsComponent = static_cast<ComponentRigibody*>((*entityList)[i]->GetComponentEditable(physicsID));

		if (transfComponent &&
			physicsComponent) {
			// Fetch values
			float gravity = physicsComponent->GetGravity();
			vec3 acc = physicsComponent->GetAcceleration();
			vec3 vel = physicsComponent->GetVelocity();

			const vec4* position = transfComponent->GetPosition();

			// Calculate physics
			if (physicsComponent->IsGravityAffected()) {
				acc.y -= gravity * (float)deltaTime;
			}

			float frictionValue = 0.97f;
			vel.x += (acc.x * (float)deltaTime);
			vel.y += (acc.y * (float)deltaTime);
			vel.z += (acc.z * (float)deltaTime);
			vel *= frictionValue;

			// Set values
			//physicsComponent->SetAcceleration(acc.x, acc.y, acc.z);
			physicsComponent->SetAcceleration(0, 0, 0);
			physicsComponent->SetVelocity(vel.x, vel.y, vel.z);

			transfComponent->SetPosition(
				position->x + (vel.x * (float)deltaTime),
				position->y + (vel.y * (float)deltaTime),
				position->z + (vel.z * (float)deltaTime)
			);
		}
	}
}