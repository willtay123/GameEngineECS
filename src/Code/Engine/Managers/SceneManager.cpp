#include "SceneManager.h"


using namespace EngineECS;


SceneManager* SceneManager::Instance = nullptr;

SceneManager& SceneManager::GetInstance() {
	if (Instance == NULL) {
		Instance = new SceneManager();
	}
	return *Instance;
}

SceneManager::SceneManager() :
	_currentSceneID(),
	_currentScene(nullptr) {
}

SceneManager::~SceneManager() {
}

void SceneManager::AddScene(const string& sceneID, std::unique_ptr<IScene> scene) {
	if (_sceneMap.size() == 0) {
		_currentScene = scene.get();
		_currentSceneID = sceneID;
	}
	scene->Initialise();
	_sceneMap[sceneID] = std::move(scene);
}

bool SceneManager::RemoveScene(const string& sceneID) {
	if (_currentSceneID == sceneID) {
		return false;
		Logger::LogError("Cannot the delete active scene");
	}

	if (!HasScene(sceneID)) {
		return false;
		Logger::LogWarning("Attempted to delete scene that doesn't exist");
	}

	// Delete map entry
	_sceneMap.erase(sceneID);
	Logger::LogInfo("Scene deleted with ID: " + sceneID);
}

bool SceneManager::HasScene(const string& sceneID) {
	// Look in map
	auto itr = _sceneMap.find(sceneID);
	return (itr != _sceneMap.end());
}

void SceneManager::SetScene(const string& sceneID) {
	if (HasScene(sceneID)) {
		// Match found, set active scene
		_currentSceneID = sceneID;
		_currentScene = _sceneMap[sceneID].get();
		Logger::LogInfo("Scene Set: " + sceneID);
	}
}

void SceneManager::SetScene(const string& sceneID, std::unique_ptr<IScene> scene) {
	// Add scene to the map
	AddScene(sceneID, std::move(scene));
	// Set that scene
	SetScene(sceneID);
}

void SceneManager::Update(double dt) {
	if (_currentScene != nullptr) { _currentScene->Update(dt); }
}

void SceneManager::Render() {
	if (_currentScene != nullptr) { _currentScene->Render(); }
}