#include <iostream>
#include "Engine.h"
#include "Managers/SceneManager.h"
#include "Externals/Scenes/TestScene.h"
#include "Externals/Implementations/RendererGL.h"
#include "Externals/Assets/Shaders/ShaderGLSL.h"
#include "Externals/Implementations/ResourceLoader.h"
#include "Externals/Implementations/CollisionDetector.h"
#include "Externals/Implementations/CollisionResponder.h"

using namespace std;

int main(void)
{	
	RendererGL* renderer = new RendererGL();
	ShaderGLSL* shader = new ShaderGLSL();
	ResourceLoader* resourceLoader = new ResourceLoader();
	ICollisionDetector* collisionDetector = new CollisionDetector();
	ICollisionResponder* collisionResponder = new CollisionResponder();
	Engine engine;
	bool engineInitialised = engine.Initialise(renderer, shader, resourceLoader, collisionDetector, collisionResponder);

	if (engineInitialised) {
		IScene* scene = new TestScene();
		engine.SetInitialScene("game", scene);

		while (true) {
			engine.Update();
			engine.Render();
		}
	}

	engine.End();

	return 0;
}