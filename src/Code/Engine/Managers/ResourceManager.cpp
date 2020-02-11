#include "ResourceManager.h"
#include <Tools\Logger.h>

using namespace EngineECS;


map<string, Texture*> ResourceManager::_textureMap;
map<string, Geometry*> ResourceManager::_modelMap;
map<string, IResource*> ResourceManager::_resourceMap;

IResourceLoader* ResourceManager::_resourceLoader;

void ResourceManager::Initialise(IResourceLoader* resourceLoader) {
	_resourceLoader = resourceLoader;
}

Texture* ResourceManager::LoadTexture(string filepath) {
	string text = string("Loading texture: " + filepath);
	Logger::LogInfo(text);

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

	string text = string("new _textureMap size: " + _textureMap.size());
	Logger::LogInfo(text);
}

Geometry* ResourceManager::LoadGeometry(string filepath) {
	string text = string("Loading Geometry: " + filepath);
	Logger::LogInfo(text);

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

	string text = string("new _modelMap size: " + _modelMap.size());
	Logger::LogInfo(text);
}

IResource* ResourceManager::LoadResource(string filepath) {
	string text = string("Loading resource: " + filepath);
	Logger::LogInfo(text);

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

	string text = string("new _resourceMap size: " + _resourceMap.size());
	Logger::LogInfo(text);
}

void ResourceManager::End() {
	//delete objects
	delete _resourceLoader;
}