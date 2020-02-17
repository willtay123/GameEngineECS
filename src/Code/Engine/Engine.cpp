// Engine.cpp : Defines the functions for the static library.
//

#include "Engine.h"

using namespace EngineECS;

double Engine::dt = 0;

Engine::Engine() :
	_initialised(false),
	_now(),
	_lastTime() {
	Logger::LogInfo("Engine creation started");
	Logger::LogInfo("Engine creation ended");
}

Engine::~Engine() {
	RenderManager::End();
	ComponentManager::End();
	SystemManager::End();
	MessageManager::End();
	ResourceManager::End();
	CollisionManager::End();
}

bool Engine::Initialise(
	IRenderer* renderer,
	IShader* shader,
	IResourceLoader* resourceLoader,
	ICollisionDetector* collisionDetector,
	ICollisionResponder* collisionResponder
) {
	Logger::LogInfo("Engine initialisation started");


	// Initialise and create managers
	Logger::LogInfo("Initialising Managers");

	RenderManager::Initialise(renderer, shader);
	ComponentManager::Initialise();
	SystemManager::Initialise();
	MessageManager::Initialise();
	ResourceManager::Initialise(resourceLoader);
	CollisionManager::Initialise(collisionDetector, collisionResponder);

	Logger::LogInfo("Managers Initialised");

	// Delta Time
	_lastTime = clock();

	Logger::LogInfo("Engine initialisation ended");

	_initialised = true;
	return true;
}

void Engine::SetInitialScene(string& sceneID, IScene* scene) {
	SceneManager::GetInstance().SetScene(sceneID, scene);
}

void Engine::Update() {
	RenderManager::StartUpdate();

	// DT
	_now = clock();
	dt = (static_cast<double>(_now) - static_cast<double>(_lastTime)) / 1000;
	_lastTime = clock();

	SceneManager::GetInstance().Update(dt);

	RenderManager::EndUpdate();
	EntityManager::EnactRemovals();
}

void Engine::Render() {
	RenderManager::StartRender();

	SceneManager::GetInstance().Render();

	RenderManager::EndRender();
}

double Engine::GetDT() {
	return dt;
}

void Engine::End() {
	SceneManager::End();
	ResourceManager::End();
	ComponentManager::End();
	RenderManager::End();
}