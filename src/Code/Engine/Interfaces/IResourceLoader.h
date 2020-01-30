#pragma once

#include "Objects/Texture.h"
#include "Objects/Geometry.h"
#include "Interfaces/IResource.h"


namespace EngineECS {
	class IResourceLoader {
	private:

	public:
		virtual Texture* LoadTexture(const char* filepath) = 0;
		virtual Geometry* LoadGeometry(const char* filepath) = 0;
		virtual IResource* LoadResource(const char* filepath) = 0;
	};
}