#include "ResourceManager.h"

using namespace EngineECS;


ResourceManager* ResourceManager::Instance = nullptr;

ResourceManager::ResourceManager() :
	_textureMap(),
	_modelMap(),
	_resourceMap(),
	_resourceLoader() {

}

ResourceManager::~ResourceManager() {
	delete _resourceLoader;

	for (auto itr = _textureMap.begin(); itr != _textureMap.end(); itr++) {
		delete itr->second;
	}
	_textureMap.clear();

	for (auto itr = _modelMap.begin(); itr != _modelMap.end(); itr++) {
		delete itr->second;
	}
	_modelMap.clear();

	for (auto itr = _resourceMap.begin(); itr != _resourceMap.end(); itr++) {
		delete itr->second;
	}
	_resourceMap.clear();
}

ResourceManager& ResourceManager::GetInstance() {
	if (!Instance) {
		Instance = new ResourceManager();
	}
	return *Instance;
}

void ResourceManager::SetResourceLoader(IResourceLoader* resourceLoader) {
	_resourceLoader = resourceLoader;
}

Texture* ResourceManager::LoadTexture(string filepath) {
	Logger::LogInfo("Loading texture: " + filepath);

	if (!_resourceLoader) {
		Logger::LogError("No resource loader has been set");
		return NULL;
	}

	Texture* texture;

	auto it = _textureMap.find(filepath);
	if (it != _textureMap.end()) {
		Logger::LogInfo("- fetched from _textureMap");
		texture = it->second;
	}
	else {
		texture = _resourceLoader->LoadTexture(filepath);

		if (texture != NULL) {
			// Add to map
			_textureMap[filepath] = texture;
		}
	}

	return texture;
}

void ResourceManager::ClearTextures() {
	Logger::LogInfo("Clearing: _textureMap");

	// Delete all contents
	for (map<string, Texture*>::iterator itr = _textureMap.begin();
		itr != _textureMap.end();
		itr++)
	{
		//for all the elements of the map
		delete itr->second;
		_textureMap.erase(itr);
	}

	std::stringstream ss = std::stringstream();
	ss << "new _textureMap size: ";
	ss << _textureMap.size();
	string text = ss.str();
	Logger::LogInfo(text);
}

Geometry* ResourceManager::LoadGeometry(string filepath) {
	Logger::LogInfo("Loading Geometry: " + filepath);

	if (!_resourceLoader) {
		Logger::LogError("No resource loader has been set");
		return NULL;
	}

	Geometry* model;

	auto it = _modelMap.find(filepath);
	if (it != _modelMap.end()) {
		// Fetch from map
		Logger::LogInfo("- fetched from _modelMap");
		model = it->second;
	}
	else {
		// Load new model
		model = _resourceLoader->LoadGeometry(filepath);

		if (model != NULL) {
			// Add to map
			_modelMap[filepath] = model;
		}
	}

	return model;
}

void ResourceManager::ClearModels() {
	Logger::LogInfo("Clearing: _modelMap");

	// Delete all contents
	for (map<string, Geometry*>::iterator itr = _modelMap.begin();
		itr != _modelMap.end();
		itr++)
	{
		//for all the elements of the map
		delete itr->second;
		_modelMap.erase(itr);
	}

	std::stringstream ss = std::stringstream();
	ss << "new _modelMap size: ";
	ss << _modelMap.size();
	string text = ss.str();
	Logger::LogInfo(text);
}

IResource* ResourceManager::LoadResource(string filepath) {
	Logger::LogInfo("Loading resource: " + filepath);

	if (!_resourceLoader) {
		Logger::LogError("No resource loader has been set");
		return NULL;
	}

	IResource* resource;

	auto it = _resourceMap.find(filepath);
	if (it != _resourceMap.end()) {
		Logger::LogInfo("- fetched from _resourceMap");
		resource = it->second;
	}
	else {
		resource = _resourceLoader->LoadResource(filepath);

		if (resource != NULL) {
			// Add to map
			_resourceMap[filepath] = resource;
		}
	}

	return resource;
}

void ResourceManager::ClearResources() {
	Logger::LogInfo("Clearing: _resourceMap");

	// Delete all contents
	for (map<string, IResource*>::iterator itr = _resourceMap.begin();
		itr != _resourceMap.end();
		itr++)
	{
		//for all the elements of the map
		delete itr->second;
		_resourceMap.erase(itr);
	}

	std::stringstream ss = std::stringstream();
	ss << "new _resourceMap size: ";
	ss << _resourceMap.size();
	string text = ss.str();
	Logger::LogInfo(text);
}