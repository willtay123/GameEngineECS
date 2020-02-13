#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "Interfaces/IResourceLoader.h"
#include "Interfaces/IResource.h"
#include "Objects/Texture.h"
#include "Objects/Geometry.h"
#include "Tools/Logger.h"

using std::map;
using std::make_pair;
using std::string;

namespace EngineECS {
	class ResourceManager {
	private:
		static map<string, Texture*> _textureMap;
		static map<string, Geometry*> _modelMap;
		static map<string, IResource*> _resourceMap;

		static IResourceLoader* _resourceLoader;

	public:
		static void Initialise(IResourceLoader* resourceLoader);

		static Texture* LoadTexture(string filepath);
		static void ClearTextures();

		static Geometry* LoadGeometry(string filepath);
		static void ClearModels();

		static IResource* LoadResource(string filepath);
		static void ClearResources();

		static void End();
	};
}