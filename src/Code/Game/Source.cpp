#pragma once
#include "Externals.h"
#include <iostream>

#include "Engine.h"
#include "Managers/SceneManager.h"
#include "Implementations/RendererGL.h"
#include "Implementations/CollisionDetector.h"
#include "Implementations/CollisionResponder.h"
#include "Implementations/ResourceLoader.h"
#include "Implementations/ExternalLogger.h"
#include "Scenes/TestScene.h"
#include "Assets/Shaders/ShaderGLSL.h"
#include <IO\EntityFactory.h>
#include "Tools\Logger.h"

using namespace std;
using namespace EngineECS;

int main(int argc, char* argv[]) {
	Logger::LogInfo("Starting Game");
	Engine engine;

	ExternalLogger* logger = new ExternalLogger();
	Logger::SetExternalLogger(logger);
	Logger::SetLoggingDestination(LoggingDestination::File);

	// Create renderers
	RendererGL* renderer = new RendererGL();
	renderer->Initialise();
	ShaderGLSL* shader = new ShaderGLSL();
	shader->Initialise();

	// Set renderers
	RenderManager::GetInstance().SetRenderer(renderer);
	RenderManager::GetInstance().SetShader(shader);

	// Create other implementations
	ResourceLoader* resourceLoader = new ResourceLoader();
	ResourceManager::GetInstance().SetResourceLoader(resourceLoader);
	ICollisionDetector* collisionDetector = new CollisionDetector();
	CollisionManager::GetInstance().SetCollisionDetector(collisionDetector);
	ICollisionResponder* collisionResponder = new CollisionResponder();
	CollisionManager::GetInstance().SetCollisionResponder(collisionResponder);

	// Initialise engine
	bool successfulInit = engine.Initialise();

	//Logger::LogInfo("inf", "info");
	//Logger::LogWarning("war", "warning");
	//Logger::LogError("err", "error");

	if (engine.GetState() == EngineState::Initialised) {
		// Set first scene
		std::unique_ptr<IScene> scene(new TestScene());
		engine.SetInitialScene("game", std::move(scene));

		if (engine.GetState() == EngineState::CanRun) {
			engine.Run();
		}
	}

	engine.End();

	char ch;
	cin >> ch;
}