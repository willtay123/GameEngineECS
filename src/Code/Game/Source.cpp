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

	RendererGL* renderer = new RendererGL();
	ShaderGLSL* shader = new ShaderGLSL();
	ResourceLoader* resourceLoader = new ResourceLoader();
	ICollisionDetector* collisionDetector = new CollisionDetector();
	ICollisionResponder* collisionResponder = new CollisionResponder();

	// Set first scene
	std::unique_ptr<IScene> scene(new TestScene());
	engine.SetInitialScene("game", std::move(scene));

	// Initialise engine
	bool engineInitialised = engine.Initialise();

	ExternalLogger* logger = new ExternalLogger();
	Logger::SetExternalLogger(logger);
	Logger::SetLoggingDestination(LoggingDestination::File);

	Logger::LogInfo("inf", "info");
	Logger::LogWarning("war", "warning");
	Logger::LogError("err", "error");

	if (engineInitialised) {
		while (true) {
			engine.Update();
			engine.Render();
		}
	}

	engine.End();

	char ch;
	cin >> ch;
}