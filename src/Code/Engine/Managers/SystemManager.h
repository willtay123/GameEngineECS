#pragma once

#include <vector>
#include "Interfaces/ISystem.h"
#include "Managers/EntityManager.h"


using std::vector;

namespace EngineECS {
	class SystemManager {
	private:
		static vector<ISystem*> _updateSystems;
		static vector<ISystem*> _renderSystems;
	public:
		static void Initialise();

		static void AddUpdateSystem(ISystem* system);
		static void AddRenderSystem(ISystem* system);

		static void ClearUpdateSystems();
		static void ClearRenderSystems();

		static void ActionUpdateSystems(double deltaTime, const string& entityGroup);
		static void ActionRenderSystems(double deltaTime, const string& entityGroup);

		static const vector<ISystem*>* GetUpdateSystems() { return &_updateSystems; }
		static const vector<ISystem*>* GetRenderSystems() { return &_renderSystems; }

		static void End();
	};
}