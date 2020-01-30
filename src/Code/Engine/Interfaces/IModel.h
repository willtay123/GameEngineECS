#pragma once

#include "Objects\Geometry.h"
#include "IResource.h"


namespace EngineECS {
	class IModel : public IResource {
	private:


	public:

		virtual void GenerateBuffers(Geometry* geometry) = 0;
	};
}