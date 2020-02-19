#pragma once

#include "Objects\Geometry.h"
#include "IResource.h"


namespace EngineECS {
	class IModel : public IResource {
	private:


	public:
		virtual ~IModel() = 0;

		virtual void GenerateBuffers(Geometry* geometry) = 0;
	};
}