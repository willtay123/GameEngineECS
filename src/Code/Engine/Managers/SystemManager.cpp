#include "SystemManager.h"

using namespace EngineECS;

vector<ISystem*> SystemManager::_updateSystems;
vector<ISystem*> SystemManager::_renderSystems;


void SystemManager::Initialise() {

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

void SystemManager::ActionUpdateSystems(double deltaTime, string& entityGroup) {
	vector<Entity*>* entityList = EntityManager::GetEntitiesEditable(entityGroup);
	for (ISystem* system : _updateSystems) {
		system->GiveEntities(entityList);
		system->OnAction(deltaTime);
	}
}

void SystemManager::ActionRenderSystems(double deltaTime, string& entityGroup) {
	vector<Entity*>* entityList = EntityManager::GetEntitiesEditable(entityGroup);
	for (ISystem* system : _renderSystems) {
		system->GiveEntities(entityList);
		system->OnAction(deltaTime);
	}
}

void SystemManager::End() {

}