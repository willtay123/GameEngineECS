#pragma once

#include <string>
#include <vector>
#include "Objects\Entity.h"

using std::string;
using std::vector;

class ISystem {
public:
	virtual const string* GetName() = 0;

	virtual void GiveEntities(vector<Entity*>* entityList) = 0;
	virtual void OnAction(double deltaTime) = 0;
};