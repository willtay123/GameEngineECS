#pragma once

#include <vector>
#include "Interfaces/ISystem.h"
#include "Managers/EntityManager.h"


using std::vector;


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

	static void ActionUpdateSystems(double deltaTime, const char* entityGroup);
	static void ActionRenderSystems(double deltaTime, const char* entityGroup);

	static void End();
};