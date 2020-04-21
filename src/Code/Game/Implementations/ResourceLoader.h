#pragma once

#include <SOIL/src/SOIL.h>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <GLM/glm/vec2.hpp>
#include <GLM/glm/vec3.hpp>

#include "Interfaces/IResourceLoader.h"
#include "Interfaces/IResource.h"
#include "Objects/Texture.h"
#include "Objects/Geometry.h"

using namespace EngineECS;
using std::ifstream;
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