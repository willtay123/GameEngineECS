#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>

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
		static ResourceManager* Instance;
		map<string, Texture*> _textureMap;
		map<string, Geometry*> _modelMap;
		map<string, IResource*> _resourceMap;

		IResourceLoader* _resourceLoader;

		ResourceManager();

	public:
		~ResourceManager();
		static ResourceManager& GetInstance();

		void SetResourceLoader(IResourceLoader* _resourceLoader);

		Texture* LoadTexture(string filepath);
		void ClearTextures();

		Geometry* LoadGeometry(string filepath);
		void ClearModels();

		IResource* LoadResource(string filepath);
		void ClearResources();
	};
}