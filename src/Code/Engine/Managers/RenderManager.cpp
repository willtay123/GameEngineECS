#include "RenderManager.h"

using namespace EngineECS;


RenderManager* RenderManager::Instance = nullptr;

RenderManager::RenderManager() :
	_renderer(nullptr),
	_shader(nullptr) {

}

RenderManager::~RenderManager() {
	if (_renderer) {
		_renderer->Unload();
	}
	if (_shader) {
		_shader->Unload();
	}

	delete _renderer;
	delete _shader;
}

RenderManager& RenderManager::GetInstance() {
	if (!Instance) {
		Instance = new RenderManager();
	}
	return *Instance;
}

bool RenderManager::SetRenderer(IRenderer* renderer) {
	// Set the renderer
	_renderer = renderer;
	if (!(_renderer->Initialise())) {
		Logger::LogError("IRenderer failed to initialise");
		return false;
	}
	return true;
}

bool RenderManager::SetShader(IShader* shader) {
	// Set the shader
	_shader = shader;
	if (!(_shader->Initialise())) {
		Logger::LogError("IShader failed to initialise");
		return false;
	}
	return true;
}

IBufferID* RenderManager::LoadShader(const string& filename, const ShaderType shaderType) {
	IBufferID* shaderID = _shader->LoadShader(filename, shaderType);

	return shaderID;
}

void RenderManager::Draw(const Camera& camera, const shared_ptr<const Entity> entity) {
	if (_renderer) {
		_renderer->Draw(camera, entity);
	}
}

void RenderManager::Draw(const Camera& camera, const std::shared_ptr<const EntityList> entityList) {
	if (_renderer) {
		_renderer->Draw(camera, entityList);
	}
}

void RenderManager::BeforeUpdate() {
	if (_renderer) {
		_renderer->StartUpdate();
	}
}

void RenderManager::AfterUpdate() {
	if (_renderer) {
		_renderer->EndUpdate();
	}
}

void RenderManager::BeforeRender() {
	if (_renderer) {
		_renderer->StartRender();
	}
}

void RenderManager::AfterRender() {
	if (_renderer) {
		_renderer->EndRender();
	}
}