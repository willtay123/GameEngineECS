#pragma once

#include <iostream>
#include <time.h>

#include "IO\Mouse.h"
#include "IO\Keyboard.h"

#include "Managers/Managers.h"
#include "Interfaces/IRenderer.h"
#include "Interfaces/IShader.h"
#include "Interfaces/IResourceLoader.h"

class Engine {
private:
	bool initialised;

	static double dt;
	clock_t now;
	clock_t lastTime;

	SceneManager* sceneManager;

public:
	static double GetDT();

	Engine();
	~Engine();

	bool Initialise(IRenderer* renderer, IShader* shader, IResourceLoader* resourceLoader, ICollisionDetector* collisionDetector, ICollisionResponder* collisionResponder);
	void SetInitialScene(const char* sceneID, IScene* scene);

	void Update();
	void Render();
	static void End();
};