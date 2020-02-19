#pragma once

#include <string>
#include <vector>
#include "Objects\Entity.h"

using std::string;
using std::vector;

namespace EngineECS {
	class ISystem {
	public:
		virtual ~ISystem() = 0;

		virtual const string* GetName() = 0;

		virtual void GiveEntities(vector<Entity*>* entityList) = 0;
		virtual void OnAction(double deltaTime) = 0;
	};
}