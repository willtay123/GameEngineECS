#pragma once

#include "CleverPointers.h"
#include "Interfaces/IResource.h"
#include "DataStructs/ResourceTypes.h"

namespace EngineECS {
	struct ResourceData {
		ResourceType _resourceType;
		shared_ptr<IResource> _resource;

		ResourceData() {
			_resourceType = ResourceType::Unspecified;
			_resource = std::make_shared<IResource>();
		}

		ResourceData(ResourceType type, shared_ptr<IResource> resource) {
			_resourceType = type;
			_resource = resource;
		}
	};
}