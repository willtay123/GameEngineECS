#include "Externals.h"
#include <iostream>

#include "Engine.h"
#include "Managers/SceneManager.h"
#include "Implementations/RendererGL.h"
#include "Implementations/CollisionDetector.h"
#include "Implementations/CollisionResponder.h"
#include "Implementations/ResourceLoader.h"
#include "Scenes/TestScene.h"
#include "Assets/Shaders/ShaderGLSL.h"
#include <IO\EntityFactory.h>
#include <Tools\Logger.h>

using namespace std;
using namespace EngineECS;

int main(int argc, char* argv[]) {
	cout << "Starting Game" << endl;

	RendererGL* renderer = new RendererGL();
	ShaderGLSL* shader = new ShaderGLSL();
	ResourceLoader* resourceLoader = new ResourceLoader();
	ICollisionDetector* collisionDetector = new CollisionDetector();
	ICollisionResponder* collisionResponder = new CollisionResponder();
	Engine engine;
	bool engineInitialised = engine.Initialise(renderer, shader, resourceLoader, collisionDetector, collisionResponder);

	Logger* logger = Logger::GetInstance();
	string t1 = string("logger1");
	logger->SetLoggingDestination(LoggingDestination::External);
	logger->LogInfo(t1);
	logger->LogError("text");

	if (engineInitialised) {
		IScene* scene = new TestScene();
		engine.SetInitialScene("game", scene);

		while (true) {
			engine.Update();
			engine.Render();
		}
	}

	engine.End();

	char ch;
	cin >> ch;
}