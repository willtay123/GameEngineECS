#pragma once

#include <string>
#include "Objects/Texture.h"
#include "Objects/Geometry.h"
#include "Interfaces/IResource.h"

using std::string;

namespace EngineECS {
	class IResourceLoader {
	private:

	public:
		virtual ~IResourceLoader() = 0;

		virtual Texture* LoadTexture(string filepath) = 0;
		virtual Geometry* LoadGeometry(string filepath) = 0;
		virtual IResource* LoadResource(string filepath) = 0;
	};
}