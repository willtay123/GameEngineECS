#include "RenderManager.h"


namespace EngineECS {
	IRenderer* RenderManager::_renderer = NULL;
	IShader* RenderManager::_shader = NULL;

	void RenderManager::Initialise(IRenderer* renderer, IShader* shader) {
		// Set the renderer
		_renderer = renderer;
		if (!(_renderer->Initialise())) {
			throw "IRenderer failed to initialise";
		}

		// Set the shader
		_shader = shader;
		if (!(_shader->Initialise())) {
			throw "IShader failed to initialise";
		}
	}

	IBufferID* RenderManager::LoadShader(const char* filename, ShaderType shaderType) {
		IBufferID* shaderID = _shader->LoadShader(filename, shaderType);

		return shaderID;
	}

	void RenderManager::Draw(const Camera* camera, const Entity* entity) {
		// Pass on to an IRenderer

		_renderer->Draw(camera, entity);
	}

	void RenderManager::Draw(const Camera* camera, const vector<Entity*>* entityList) {
		_renderer->Draw(camera, entityList);
	}

	void RenderManager::StartUpdate() {
		_renderer->StartUpdate();
	}

	void RenderManager::EndUpdate() {
		_renderer->EndUpdate();
	}

	void RenderManager::StartRender() {
		_renderer->StartRender();
	}

	void RenderManager::EndRender() {
		_renderer->EndRender();
	}

	void RenderManager::End() {
		//delete objects;
		_renderer->Unload();
		_shader->Unload();
	}
}