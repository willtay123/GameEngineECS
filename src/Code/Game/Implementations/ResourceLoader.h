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
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

class ResourceLoader : public IResourceLoader {
private:

public:

	Texture* LoadTexture(const char* filepath);
	Geometry* LoadGeometry(const char* filepath);
	IResource* LoadResource(const char* filepath);

	Geometry* LoadOBJ(const char* filpath);
};