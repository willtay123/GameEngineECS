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
	enum class EngineState {
		Uninitialised,
		Initialised,
		CanRun,
		Running
	};

	class Engine {
	private:
		static double dt;
		EngineState _engineState;
		clock_t _now;
		clock_t _lastTime;

	public:
		static double GetDT();

		Engine();
		Engine(const Engine& rhs) = delete;
		~Engine();
		Engine& operator=(const Engine& rhs) = delete;

		bool Initialise();
		void SetInitialScene(const string& sceneID, std::unique_ptr<IScene> scene);

		EngineState GetState() const { return _engineState; }
		bool IsState(EngineState state) { return (_engineState == state); }

		void Run();
		void Update();
		void Render();
		static void End();
	};
}