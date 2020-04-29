#pragma once

#include <vector>
#include "Interfaces/ISystem.h"
#include "Managers/EntityManager.h"
#include "CleverPointers.h"


using std::vector;

namespace EngineECS {
	class SystemManager {
	private:
		static SystemManager* Instance;
		vector<shared_ptr<ISystem>> _updateSystems;
		vector<shared_ptr<ISystem>> _renderSystems;

		SystemManager();
	public:
		~SystemManager();
		static SystemManager& GetInstance();

		void AddUpdateSystem(shared_ptr<ISystem> system);
		void AddRenderSystem(shared_ptr<ISystem> system);

		void ClearUpdateSystems();
		void ClearRenderSystems();

		void ActionUpdateSystems(double deltaTime);
		void ActionRenderSystems(double deltaTime);

		const vector<shared_ptr<ISystem>>& GetUpdateSystems() { return _updateSystems; }
		const vector<shared_ptr<ISystem>>& GetRenderSystems() { return _renderSystems; }
	};
}