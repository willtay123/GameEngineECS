#pragma once
#pragma once
#include "Objects\Geometry.h"
#include "IResource.h"
#include "CleverPointers.h"

namespace EngineECS {
	class IModel : public IResource {
	private:


	public:
		virtual ~IModel() {}

		virtual void GenerateBuffers(shared_ptr<Geometry> geometry) = 0;
	};
}