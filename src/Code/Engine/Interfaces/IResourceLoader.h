#pragma once

#include <memory>
#include <string>
#include "Objects/Texture.h"
#include "Objects/Geometry.h"
#include "Interfaces/IResource.h"

using std::string;

namespace EngineECS {
	class IResourceLoader {
	private:

	public:
		virtual ~IResourceLoader() {};

		virtual std::shared_ptr<Texture> LoadTexture(const string& filepath) = 0;
		virtual std::shared_ptr<Geometry> LoadGeometry(const string& filepath) = 0;
		virtual std::shared_ptr<IResource> LoadResource(const string& filepath) = 0;
	};
}