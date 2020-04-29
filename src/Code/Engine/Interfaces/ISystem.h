#pragma once

#include <string>
#include <vector>
#include "Objects\Entity.h"

using std::string;
using std::vector;

namespace EngineECS {
	class ISystem {
	public:
		virtual ~ISystem() {}

		virtual const string& GetName() = 0;

		virtual void OnAction(double deltaTime) = 0;
	};
}