#pragma once

#include "pch.h"
#include "framework.h"

#include <iostream>
#include <time.h>

#include "Managers/Managers.h"
#include "Interfaces/IRenderer.h"
#include "Interfaces/IShader.h"
#include "Interfaces/IResourceLoader.h"
#include "Tools\Logger.h"


namespace EngineECS {
	class Engine {
	private:
		bool _initialised;

		static double dt;
		clock_t _now;
		clock_t _lastTime;

	public:
		static double GetDT();

		Engine();
		~Engine();

		bool Initialise(IRenderer* renderer, IShader* shader, IResourceLoader* resourceLoader, ICollisionDetector* collisionDetector, ICollisionResponder* collisionResponder);
		void SetInitialScene(const string& sceneID, IScene* scene);

		void Update();
		void Render();
		static void End();
	};
}