#include "SystemPhysics.h"



SystemPhysics::SystemPhysics() {
	_name = new string("Physics System");
}

SystemPhysics::~SystemPhysics() {

}

const string* SystemPhysics::GetName() {
	return _name;
}

void SystemPhysics::GiveEntities(vector<Entity*>* entityList) {
	_entityList = entityList;
}

void SystemPhysics::OnAction(double deltaTime) {
	int transformID = ComponentManager::GetIDForString("Transform");
	int physicsID = ComponentManager::GetIDForString("Physics");

	for (Entity* entity : (*_entityList)) {
		ComponentTransform* transfComponent = static_cast<ComponentTransform*>(entity->GetComponentEditable(transformID));
		ComponentPhysics* physicsComponent = static_cast<ComponentPhysics*>(entity->GetComponentEditable(physicsID));

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