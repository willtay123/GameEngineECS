#include "SceneManager.h"


using namespace EngineECS;


SceneManager* SceneManager::Instance;

SceneManager& SceneManager::GetInstance() {
	if (Instance == NULL) {
		Instance = new SceneManager();
	}
	return *Instance;
}

SceneManager::SceneManager() :
	_scene(nullptr) {
}

SceneManager::~SceneManager() {
	delete _scene;
}

void SceneManager::AddScene(const string& sceneID, IScene* scene) {
	// NOTE: may want to check for existing scene and throw exception
	scene->Initialise();
	_sceneMap[sceneID] = scene;
}

void SceneManager::RemoveScene(const string& sceneID) {
	// Look in map
	auto itr = _sceneMap.find(sceneID);
	if (itr != _sceneMap.end()) {
		// Match found
		_scene = itr->second;

		// Delete scene object
		delete _scene;

		// Delete map entry
		_sceneMap.erase(sceneID);

		string text = "Scene deleted with ID: " + sceneID;
		Logger::LogInfo(text);
	}
	else {
		// Scene not found
		string text = "Scene not found: " + sceneID;
		Logger::LogError(text);
	}
}

bool SceneManager::HasScene(const string& sceneID) {
	// Look in map
	auto itr = _sceneMap.find(sceneID);
	if (itr != _sceneMap.end()) {
		// Match found
		return true;
	}
	else {
		// Match not found
		return false;
	}
}

void SceneManager::SetScene(const string& sceneID) {
	// Look in map
	auto itr = _sceneMap.find(sceneID);
	if (itr != _sceneMap.end()) {
		// Match found, set active scene
		_scene = itr->second;
		string text = "Scene Set: " + *(_scene->GetName());
		Logger::LogInfo(text);
	}
	else {
		// Scene not found
		string text = "Scene not found: " + sceneID;
		Logger::LogError(text);
	}
}

void SceneManager::SetScene(const string& sceneID, IScene* scene) {
	// Add scene to the map
	AddScene(sceneID, scene);
	// Set that scene
	SetScene(sceneID);
}

void SceneManager::Update(double dt) {
	if (!_scene) {
		_scene = new DefaultScene();
	}
	_scene->Update(dt);
}

void SceneManager::Render() {
	if (!_scene) {
		_scene = new DefaultScene();
	}
	_scene->Render();
}

void SceneManager::End() {
	//delete objects
}