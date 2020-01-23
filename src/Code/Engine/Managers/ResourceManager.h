#pragma once

#include <iostream>
#include <map>
#include <vector>

#include "Interfaces/IResourceLoader.h"
#include "Interfaces/IResource.h"
#include "Objects/Texture.h"
#include "Objects/Geometry.h"

using std::map;
using std::make_pair;
using std::cout;
using std::endl;

class ResourceManager {
private:
	static map<const char*, Texture*> _textureMap;
	static map<const char*, Geometry*> _modelMap;
	static map<const char*, IResource*> _resourceMap;

	static IResourceLoader* _resourceLoader;

public:
	static void Initialise(IResourceLoader* resourceLoader);

	static Texture* LoadTexture(const char* filepath);
	static void ClearTextures();

	static Geometry* LoadGeometry(const char* filepath);
	static void ClearModels();

	static IResource* LoadResource(const char* filepath);
	static void ClearResources();

	static void End();
};