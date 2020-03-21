#include "SceneManager.h"


using namespace EngineECS;


SceneManager* SceneManager::Instance = nullptr;

SceneManager& SceneManager::GetInstance() {
	if (Instance == NULL) {
		Instance = new SceneManager();
	}
	return *Instance;
}

SceneManager::SceneManager() {
}

SceneManager::~SceneManager() {
}

void SceneManager::AddScene(unique_ptr<IScene> scene) {
	scene->Initialise();
	_scenes.push(move(scene));
}

void SceneManager::RemoveScene() {
	// Delete current scene
	Logger::LogInfo("Scene deleted with ID: " + _scenes.top()->GetName());
	_scenes.pop(); // If user calls this from the current scene, undefined behaviour
}

void SceneManager::SwapScene(unique_ptr<IScene> scene) {
	RemoveScene();
	AddScene(move(scene));
}

void SceneManager::Update(double dt) {
	if (_scenes.top() != nullptr) { _scenes.top()->Update(dt); }
}

void SceneManager::Render() {
	if (_scenes.top() != nullptr) { _scenes.top()->Render(); }
}