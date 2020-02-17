#include "SystemManager.h"

using namespace EngineECS;



SystemManager::SystemManager() :
	_updateSystems(),
	_renderSystems() {

}

SystemManager::~SystemManager() {
	for (ISystem* system : _updateSystems) {
		delete system;
	}
	_updateSystems.clear();
	for (ISystem* system : _renderSystems) {
		delete system;
	}
	_renderSystems.clear();
}

SystemManager& SystemManager::GetInstance() {
	if (!Instance) {
		Instance = new SystemManager();
	}
	return *Instance;
}

void SystemManager::AddUpdateSystem(ISystem* system) {
	_updateSystems.push_back(system);
}

void SystemManager::AddRenderSystem(ISystem* system) {
	_renderSystems.push_back(system);
}

void SystemManager::ClearUpdateSystems() {
	for (ISystem* system : _updateSystems) {
		delete system;
	}
	_updateSystems.clear();
}

void SystemManager::ClearRenderSystems() {
	for (ISystem* system : _renderSystems) {
		delete system;
	}
	_renderSystems.clear();
}

void SystemManager::ActionUpdateSystems(double deltaTime, const string& entityGroup) {
	vector<Entity*>* entityList = EntityManager::GetInstance().GetEntitiesEditable(entityGroup);
	for (ISystem* system : _updateSystems) {
		system->GiveEntities(entityList);
		system->OnAction(deltaTime);
	}
}

void SystemManager::ActionRenderSystems(double deltaTime, const string& entityGroup) {
	vector<Entity*>* entityList = EntityManager::GetInstance().GetEntitiesEditable(entityGroup);
	for (ISystem* system : _renderSystems) {
		system->GiveEntities(entityList);
		system->OnAction(deltaTime);
	}
}
