#pragma once
#include "Interfaces/ISystem.h"

#include <vector>
#include <string>

#include "Managers/ComponentManager.h"
#include "Objects/Entity.h"
#include "Components/ComponentTransform.h"
#include "Externals/Components/ComponentPhysics.h"

using std::vector;
using std::string;

class SystemPhysics : public ISystem {
private:
	string* _name;
	vector<Entity*>* _entityList;

public:
	SystemPhysics();
	~SystemPhysics();

	const string* GetName();

	void GiveEntities(vector<Entity*>* entityList);
	void OnAction(double deltaTime);
};