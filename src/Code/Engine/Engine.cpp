// Engine.cpp : Defines the functions for the static library.
//

#include "Engine.h"

using namespace EngineECS;

double Engine::dt = 0;

Engine::Engine() :
	_engineState(EngineState::Uninitialised),
	_now(),
	_lastTime() {
	Logger::LogInfo("Engine creation started");
	Logger::LogInfo("Engine creation ended");
}

Engine::~Engine() {
}

bool Engine::Initialise() {
	Logger::LogInfo("Engine initialisation started");

	Logger::LogInfo("Validating managers");

	// Check for IRenderer
	if (RenderManager::GetInstance().GetRenderer() == nullptr) {
		Logger::LogError("RenderManager has no renderer set");
		return false;
	}

	// Check for IShader
	if (RenderManager::GetInstance().GetShader() == nullptr) {
		Logger::LogError("RenderManager has no shader set");
		return false;
	}

	// Check for IResourceLoader
	if (ResourceManager::GetInstance().GetResourceLoader() == nullptr) {
		Logger::LogError("ResourceManager has no resource loader set");
		return false;
	}

	// TODO: Move to "CanStart" check

	Logger::LogInfo("Finished validating managers");

	// Delta Time
	_lastTime = clock();

	Logger::LogInfo("Engine initialisation ended");

	_engineState = EngineState::Initialised;
	return true;
}

void Engine::SetInitialScene(const string& sceneID, std::unique_ptr<IScene> scene) {
	if (_engineState == EngineState::Initialised) {
		SceneManager::GetInstance().SetScene(sceneID, std::move(scene));
		_engineState = EngineState::CanRun;
	}
	else {
		Logger::LogError("Cannot set initial scene while engine is uninitialised");
	}
}

void Engine::Run() {
	if (IsState(EngineState::CanRun)) {

		// Allow the engine to run
		_engineState = EngineState::Running;

		while (IsState(EngineState::Running)) {
			Update();
			Render();
		}
	}
	else {
		Logger::LogError("Cannot run the engine without setting an initial scene");
	}
}

void Engine::Update() {
	// DT
	_now = clock();
	dt = (static_cast<double>(_now) - static_cast<double>(_lastTime)) / 1000;
	_lastTime = clock();

	// Perform update logic
	RenderManager::GetInstance().BeforeUpdate();
	SceneManager::GetInstance().Update(dt);
	RenderManager::GetInstance().AfterUpdate();

	// Remove entities marked for removal
	EntityManager::GetInstance().EnactRemovals();

	// Get the current entity list
	auto entityList = EntityManager::GetInstance().GetEntities();
	// Handle Collisions
	CollisionManager::GetInstance().DetectCollisions(entityList);
	CollisionManager::GetInstance().HandleCollisions();
}

void Engine::Render() {
	RenderManager::GetInstance().BeforeRender();
	SceneManager::GetInstance().Render();
	RenderManager::GetInstance().AfterRender();
}

double Engine::GetDT() {
	return dt;
}

void Engine::End() {
}