#include "ResourceManager.h"


map<const char*, Texture*> ResourceManager::_textureMap;
map<const char*, Geometry*> ResourceManager::_modelMap;
map<const char*, IResource*> ResourceManager::_resourceMap;

IResourceLoader* ResourceManager::_resourceLoader;

void ResourceManager::Initialise(IResourceLoader* resourceLoader) {
	_resourceLoader = resourceLoader;
}

Texture* ResourceManager::LoadTexture(const char* filepath) {
	std::cout << "Loading texture: " << filepath << std::endl;

	Texture* texture;

	auto it = _textureMap.find(filepath);
	if (it != _textureMap.end()) {
		cout << "- fetched from _textureMap" << endl;
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
	cout << "Clearing: _textureMap" << endl;

	// Delete all contents
	for (map<const char*, Texture*>::iterator itr = _textureMap.begin();
		itr != _textureMap.end();
		itr++)
	{
		//for all the elements of the map
		delete itr->second;
		_textureMap.erase(itr);
	}

	cout << "new _textureMap size: " << _textureMap.size() << endl;
}

Geometry* ResourceManager::LoadGeometry(const char* filepath) {
	cout << "Loading Geometry" << endl;

	Geometry* model;

	auto it = _modelMap.find(filepath);
	if (it != _modelMap.end()) {
		// Fetch from map
		cout << "- fetched from _modelMap" << endl;
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
	cout << "Clearing: _modelMap" << endl;

	// Delete all contents
	for (map<const char*, Geometry*>::iterator itr = _modelMap.begin();
		itr != _modelMap.end();
		itr++)
	{
		//for all the elements of the map
		delete itr->second;
		_modelMap.erase(itr);
	}

	cout << "new _modelMap size: " << _modelMap.size() << endl;
}

IResource* ResourceManager::LoadResource(const char* filepath) {
	std::cout << "Loading resource: " << filepath << std::endl;

	IResource* resource;

	auto it = _resourceMap.find(filepath);
	if (it != _resourceMap.end()) {
		cout << "- fetched from _resourceMap" << endl;
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
	cout << "Clearing: _resourceMap" << endl;

	// Delete all contents
	for (map<const char*, IResource*>::iterator itr = _resourceMap.begin();
		itr != _resourceMap.end();
		itr++)
	{
		//for all the elements of the map
		delete itr->second;
		_resourceMap.erase(itr);
	}

	cout << "new _resourceMap size: " << _resourceMap.size() << endl;
}

void ResourceManager::End() {
	//delete objects
	delete _resourceLoader;
}