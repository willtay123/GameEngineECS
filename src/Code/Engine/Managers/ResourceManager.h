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
#include "CleverPointers.h"

using std::map;
using std::make_pair;
using std::string;

namespace EngineECS {
	class ResourceManager {
	private:
		static ResourceManager* Instance;
		map<string, shared_ptr<Texture>> _textureMap;
		map<string, shared_ptr<Geometry>> _modelMap;
		map<string, shared_ptr<IResource>> _resourceMap;

		IResourceLoader* _resourceLoader;

		ResourceManager();

	public:
		~ResourceManager();
		static ResourceManager& GetInstance();

		void SetResourceLoader(IResourceLoader* _resourceLoader);
		IResourceLoader* GetResourceLoader() const { return _resourceLoader; }

		weak_ptr<Texture> LoadTexture(const string& filepath);
		void ClearTextures();

		weak_ptr<Geometry> LoadGeometry(const string& filepath);
		void ClearModels();

		weak_ptr<IResource> LoadResource(const string& filepath);
		void ClearResources();
	};
}