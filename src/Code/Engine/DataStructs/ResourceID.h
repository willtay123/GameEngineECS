#pragma once

#include "DataStructs/ResourceTypes.h"


namespace EngineECS {
	struct ResourceID {
		ResourceType _resourceType;
		unsigned int _resourceID;

		ResourceID() {
			_resourceType = ResourceType::Unspecified;
			_resourceID = 0;
		}

		ResourceID(ResourceType type, unsigned int resourceID) {
			_resourceType = type;
			_resourceID = resourceID;
		}
	};
}