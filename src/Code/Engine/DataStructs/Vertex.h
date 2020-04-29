#pragma once

#include "GLM/glm/vec2.hpp"
#include "GLM/glm/vec3.hpp"

using glm::vec2;
using glm::vec3;

class Vertex {
private:

public:
	vec3 pos;
	vec2 uv;
	vec3 normal;
};