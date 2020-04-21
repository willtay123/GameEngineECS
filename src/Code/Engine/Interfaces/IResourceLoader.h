#pragma once

#pragma once
#include <string>
#include "Objects/Texture.h"
#include "Objects/Geometry.h"
#include "Interfaces/IResource.h"
#include "CleverPointers.h"

using std::string;

namespace EngineECS {
	class IResourceLoader {
	private:

	public:
		virtual ~IResourceLoader() {};

		virtual shared_ptr<Texture> LoadTexture(const string& filepath) = 0;
		virtual shared_ptr<Geometry> LoadGeometry(const string& filepath) = 0;
		virtual shared_ptr<IResource> LoadResource(const string& filepath) = 0;
	};
}