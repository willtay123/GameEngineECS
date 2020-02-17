// Engine.cpp : Defines the functions for the static library.
//

#include "Engine.h"

using namespace EngineECS;

double Engine::dt = 0;

Engine::Engine() {
	Logger::LogInfo("Engine creation started");

	initialised = false;
	sceneManager = SceneManager::GetInstance();

	Logger::LogInfo("Engine creation ended");
}

Engine::~Engine() {
	delete sceneManager;
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
	lastTime = clock();

	Logger::LogInfo("Engine initialisation ended");

	initialised = true;
	return true;
}

void Engine::SetInitialScene(const char* sceneID, IScene* scene) {
	if (!initialised) {
		throw "ERROR: Engine must be initialised before a scene can be set";
	}
	sceneManager->SetScene(sceneID, scene);
}

void Engine::Update() {
	RenderManager::StartUpdate();

	// DT
	now = clock();
	dt = (static_cast<double>(now) - static_cast<double>(lastTime)) / 1000;
	lastTime = clock();

	sceneManager->Update(dt);

	RenderManager::EndUpdate();
	EntityManager::EnactRemovals();
}

void Engine::Render() {
	RenderManager::StartRender();

	sceneManager->Render();

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