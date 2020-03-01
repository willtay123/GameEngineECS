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
	_textureMap.clear();
	_modelMap.clear();
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

shared_ptr<Texture> ResourceManager::LoadTexture(const string& filepath) {
	Logger::LogInfo("Loading texture: " + filepath);

	if (!_resourceLoader) {
		Logger::LogError("No resource loader has been set");
		return shared_ptr<Texture>();
	}

	shared_ptr<Texture> texture;

	auto it = _textureMap.find(filepath);
	if (it != _textureMap.end()) {
		Logger::LogInfo("- fetched from _textureMap");
		texture = it->second;
	}
	else {
		texture = _resourceLoader->LoadTexture(filepath);

		if (texture != nullptr) {
			// Add to map
			_textureMap[filepath] = texture;
		}
	}

	return texture;
}

void ResourceManager::ClearTextures() {
	Logger::LogInfo("Clearing: _textureMap");

	// Delete all contents
	for (auto itr = _textureMap.begin();
		itr != _textureMap.end();
		itr++)
	{
		_textureMap.erase(itr);
	}

	std::stringstream ss = std::stringstream();
	ss << "new _textureMap size: ";
	ss << _textureMap.size();
	string text = ss.str();
	Logger::LogInfo(text);
}

shared_ptr<Geometry> ResourceManager::LoadGeometry(const string& filepath) {
	Logger::LogInfo("Loading Geometry: " + filepath);

	if (!_resourceLoader) {
		Logger::LogError("No resource loader has been set");
		return shared_ptr<Geometry>();
	}

	shared_ptr<Geometry> model;

	auto it = _modelMap.find(filepath);
	if (it != _modelMap.end()) {
		// Fetch from map
		Logger::LogInfo("- fetched from _modelMap");
		model = it->second;
	}
	else {
		// Load new model
		model = _resourceLoader->LoadGeometry(filepath);

		if (model != nullptr) {
			// Add to map
			_modelMap[filepath] = model;
		}
	}

	return model;
}

void ResourceManager::ClearModels() {
	Logger::LogInfo("Clearing: _modelMap");

	// Delete all contents
	for (auto itr = _modelMap.begin();
		itr != _modelMap.end();
		itr++)
	{
		//for all the elements of the map
		_modelMap.erase(itr);
	}

	std::stringstream ss = std::stringstream();
	ss << "new _modelMap size: ";
	ss << _modelMap.size();
	string text = ss.str();
	Logger::LogInfo(text);
}

shared_ptr<IResource> ResourceManager::LoadResource(const string& filepath) {
	Logger::LogInfo("Loading resource: " + filepath);

	if (!_resourceLoader) {
		Logger::LogError("No resource loader has been set");
		return shared_ptr<IResource>();
	}

	shared_ptr<IResource> resource;

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
	for (auto itr = _resourceMap.begin();
		itr != _resourceMap.end();
		itr++)
	{
		//for all the elements of the map
		_resourceMap.erase(itr);
	}

	std::stringstream ss = std::stringstream();
	ss << "new _resourceMap size: ";
	ss << _resourceMap.size();
	Logger::LogInfo(ss.str());
}