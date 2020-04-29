#include "SystemManager.h"

using namespace EngineECS;

SystemManager* SystemManager::Instance = nullptr;

SystemManager::SystemManager() :
	_updateSystems(),
	_renderSystems() {

}

SystemManager::~SystemManager() {
	_updateSystems.clear();
	_renderSystems.clear();
}

SystemManager& SystemManager::GetInstance() {
	if (!Instance) {
		Instance = new SystemManager();
	}
	return *Instance;
}

void SystemManager::AddUpdateSystem(shared_ptr<ISystem> system) {
	_updateSystems.push_back(system);
}

void SystemManager::AddRenderSystem(shared_ptr<ISystem> system) {
	_renderSystems.push_back(system);
}

void SystemManager::ClearUpdateSystems() {
	_updateSystems.clear();
}

void SystemManager::ClearRenderSystems() {
	_renderSystems.clear();
}

void SystemManager::ActionUpdateSystems(double deltaTime) {
	for (shared_ptr<ISystem> system : _updateSystems) {
		system->OnAction(deltaTime);
	}
}

void SystemManager::ActionRenderSystems(double deltaTime) {
	for (shared_ptr<ISystem> system : _renderSystems) {
		system->OnAction(deltaTime);
	}
}
