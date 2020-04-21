#pragma once

#include <vector>
#include "Interfaces/ISystem.h"
#include "Managers/EntityManager.h"


using std::vector;

namespace EngineECS {
	class SystemManager {
	private:
		static SystemManager* Instance;
		vector<ISystem*> _updateSystems;
		vector<ISystem*> _renderSystems;

		SystemManager();
	public:
		~SystemManager();
		static SystemManager& GetInstance();

		void AddUpdateSystem(ISystem* system);
		void AddRenderSystem(ISystem* system);

		void ClearUpdateSystems();
		void ClearRenderSystems();

		void ActionUpdateSystems(double deltaTime);
		void ActionRenderSystems(double deltaTime);

		const vector<ISystem*>* GetUpdateSystems() { return &_updateSystems; }
		const vector<ISystem*>* GetRenderSystems() { return &_renderSystems; }
	};
}