#pragma once
#include "Interfaces/ISystem.h"

#include <vector>
#include <string>

#include "Managers/ComponentManager.h"
#include "Objects/Entity.h"
#include "Components/ComponentTransform.h"
#include "Components/ComponentPhysics.h"

using namespace EngineECS;
using std::vector;
using std::string;

class SystemRigidBody : public ISystem {
private:
	string* _name;
	vector<Entity*>* _entityList;

public:
	SystemRigidBody();
	~SystemRigidBody();

	const string* GetName();

	void GiveEntities(vector<Entity*>* entityList);
	void OnAction(double deltaTime);
};