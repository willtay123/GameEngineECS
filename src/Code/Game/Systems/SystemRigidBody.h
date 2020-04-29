#pragma once
#include "Interfaces/ISystem.h"

#include <vector>
#include <string>

#include "Managers/EntityManager.h"
#include "Managers/ComponentManager.h"
#include "Objects/Entity.h"
#include "Components/ComponentTransform.h"
#include "Components/ComponentRigidbody.h"

using namespace EngineECS;
using std::vector;
using std::string;

class SystemRigidBody : public ISystem {
private:
	string _name;

public:
	SystemRigidBody();
	~SystemRigidBody();

	const string& GetName();

	void OnAction(double deltaTime);
};