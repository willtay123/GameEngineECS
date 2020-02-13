#pragma once

#include <iostream>
#include <Tools/Logger.h>
#include "Interfaces/IScene.h"

namespace EngineECS {
	class DefaultScene : public IScene {
	private:

	public:
		DefaultScene();
		~DefaultScene();

		void Initialise();
		void Update(double dt);
		void Render();
		void Close();
	};
}