#pragma once

#include <SOIL.h>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>

#include "Interfaces/IResourceLoader.h"
#include "Interfaces/IResource.h"
#include "Objects/Texture.h"
#include "Objects/Geometry.h"

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