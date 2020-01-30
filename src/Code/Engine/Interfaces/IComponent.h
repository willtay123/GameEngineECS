#pragma once

#include <string>

#include "Managers/ComponentManager.h"
#include "Interfaces/IMessage.h"

using std::string;

namespace EngineECS {
	class IComponent {
	protected:
		int _componentType;

	public:
		virtual IComponent* Clone() = 0;

		virtual int ComponentType() const = 0;
		virtual void Message(IMessage* message) = 0;
	};
}