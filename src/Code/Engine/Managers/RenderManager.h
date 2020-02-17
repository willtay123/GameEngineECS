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

#include "Tools/Logger.h"


using glm::vec4;
using glm::mat4;
using std::vector;

namespace EngineECS {
	class RenderManager {
	private:
		static RenderManager* Instance;
		IRenderer* _renderer;
		IShader* _shader;

		RenderManager();

	public:
		~RenderManager();
		static RenderManager& GetInstance();

		bool SetRenderer(IRenderer* renderer);
		bool SetShader(IShader* shader);

		IBufferID* LoadShader(const string& filename, const ShaderType shaderType);

		void Draw(const Camera* camera, const Entity* entity);
		void Draw(const Camera* camera, const vector<Entity*>* entities);

		void StartUpdate();
		void EndUpdate();

		void StartRender();
		void EndRender();
	};
}