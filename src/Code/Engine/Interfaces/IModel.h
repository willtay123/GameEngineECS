#pragma once

#include <memory>
#include "Objects\Geometry.h"
#include "IResource.h"


namespace EngineECS {
	class IModel : public IResource {
	private:


	public:
		virtual ~IModel() {}

		virtual void GenerateBuffers(std::shared_ptr<Geometry> geometry) = 0;
	};
}