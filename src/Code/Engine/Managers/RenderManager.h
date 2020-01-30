#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <vector>

#include <GLM/glm/vec4.hpp>
#include <GLM/glm/mat4x4.hpp>
#include <GLM/glm/gtx/transform.hpp>

#include "Interfaces/IRenderer.h"
#include "Interfaces/IShader.h"

#include "Objects/Camera.h"
#include "Objects/Entity.h"
#include "Objects/Geometry.h"

using glm::vec4;
using glm::mat4;
using std::vector;

namespace EngineECS {
	class RenderManager {
	private:

	public:
		static IRenderer* _renderer;
		static IShader* _shader;

		static void Initialise(IRenderer* renderer, IShader* shader);

		static IBufferID* LoadShader(const char* filename, ShaderType shaderType);

		static void Draw(const Camera* camera, const Entity* entity);
		static void Draw(const Camera* camera, const vector<Entity*>* entities);

		static void StartUpdate();
		static void EndUpdate();

		static void StartRender();
		static void EndRender();

		static void End();
	};
}