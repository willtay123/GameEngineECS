// Engine.cpp : Defines the functions for the static library.
//

#include "Engine.h"

namespace EngineECS {
	double Engine::dt = 0;

	Engine::Engine() {
		std::cout << "Engine creation started" << endl;

		initialised = false;
		sceneManager = SceneManager::GetInstance();

		std::cout << "Engine creation ended" << endl << endl;
	}

	Engine::~Engine() {
		delete sceneManager;
		RenderManager::End();
		EntityManager::End();
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
		std::cout << "Engine initialisation started" << endl;


		// Initialise and create managers
		std::cout << "Initialising Managers" << std::endl << std::endl;

		RenderManager::Initialise(renderer, shader);
		EntityManager::Initialise();
		ComponentManager::Initialise();
		SystemManager::Initialise();
		MessageManager::Initialise();
		ResourceManager::Initialise(resourceLoader);
		CollisionManager::Initialise(collisionDetector, collisionResponder);

		std::cout << "Managers Initialised" << std::endl << std::endl;

		// Delta Time
		lastTime = clock();

		std::cout << "Engine initialisation ended" << endl << endl;

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
		dt = (double)(now - lastTime) / 1000;
		lastTime = clock();

		sceneManager->Update(dt);

		RenderManager::EndUpdate();
		EntityManager::EnactFinal();
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
		EntityManager::End();
		ComponentManager::End();
		RenderManager::End();
	}
}