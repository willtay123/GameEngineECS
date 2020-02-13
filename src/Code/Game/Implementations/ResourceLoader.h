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

	Texture* LoadTexture(string filepath);
	Geometry* LoadGeometry(string filepath);
	IResource* LoadResource(string filepath);

	Geometry* LoadOBJ(string filpath);
};