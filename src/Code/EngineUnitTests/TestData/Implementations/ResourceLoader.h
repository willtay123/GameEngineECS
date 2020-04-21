#pragma once

#include <iostream>
#include <string>

#include "Interfaces/IResourceLoader.h"
#include "Interfaces/IResource.h"
#include "Objects/Texture.h"
#include "Objects/Geometry.h"

using namespace EngineECS;
using std::string;

class ResourceLoader : public IResourceLoader {
private:

public:
	~ResourceLoader();

	std::shared_ptr<Texture> LoadTexture(const string& filepath);
	std::shared_ptr<Geometry> LoadGeometry(const string& filepath);
	std::shared_ptr<IResource> LoadResource(const string& filepath);

	std::shared_ptr<Geometry> LoadOBJ(const string& filpath);
};