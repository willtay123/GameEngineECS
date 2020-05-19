#pragma once
#include "Externals.h"
#include <iostream>

#include "Engine.h"
#include "Managers/Managers.h"
#include "Implementations/RendererGL.h"
#include "Implementations/CollisionDetector.h"
#include "Implementations/CollisionResponder.h"
#include "Implementations/ResourceLoader.h"
#include "Implementations/ExternalLogger.h"
#include "Scenes/MainScene.h"
#include "Assets/Shaders/ShaderGLSL.h"
#include <IO\EntityFactory.h>
#include "Tools\Logger.h"

using namespace std;
using namespace EngineECS;

int main(int argc, char* argv[]) {
	Logger::LogInfo("Starting Game");

	ExternalLogger* logger = new ExternalLogger();
	Logger::SetExternalLogger(logger);
	Logger::SetLoggingDestination(LoggingDestination::Console);

	// TEMP
	NetworkManager::GetInstance().EnableNetworking("127.0.0.1");
	NetworkManager::GetInstance().SendPacket();
	NetworkManager::GetInstance().SendPacket();
	//NetworkManager::GetInstance().CloseConnection();

	// Create engine
	Engine engine;

	// Create renderers
	RendererGL* renderer = new RendererGL();
	ShaderGLSL* shader = new ShaderGLSL();

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

	if (engine.GetState() == EngineState::Initialised) {
		// Set first scene
		std::unique_ptr<IScene> scene(new MainScene());
		engine.SetInitialScene("game", std::move(scene));

		if (engine.GetState() == EngineState::CanRun) {
			engine.Run();
		}
	}

	engine.End();

	char ch;
	cin >> ch;
}