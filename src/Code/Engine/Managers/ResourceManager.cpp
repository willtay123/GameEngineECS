#include "ResourceManager.h"

using namespace EngineECS;


ResourceManager* ResourceManager::Instance = nullptr;

ResourceManager::ResourceManager() :
	_idTracker(1),
	_pathMap(),
	_resourceMap(),
	_resourceLoader() {

}

ResourceManager::~ResourceManager() {
	delete _resourceLoader;
	_resourceMap.clear();
	_pathMap.clear();
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

ResourceID ResourceManager::LoadTextureByPath(const string& filepath) {
	Logger::LogInfo("Loading texture: " + filepath);

	if (!_resourceLoader) {
		Logger::LogError("No resource loader has been set");
		return ResourceID();
	}

	ResourceID resourceID;

	auto it = _pathMap.find(filepath);
	if (it != _pathMap.end()) {
		Logger::LogInfo("Matching path for resource: " + filepath);
		return it->second;
	}
	else {
		shared_ptr<Texture> texture = _resourceLoader->LoadTexture(filepath);

		if (texture != nullptr) {
			Logger::LogInfo("Adding file to resources: " + filepath);
			int id = GetNewID();
			// Add path to map
			resourceID = ResourceID(ResourceType::Texture, id);
			_pathMap[filepath] = resourceID;
			// Add resource to map
			_resourceMap[id] = ResourceData(ResourceType::Texture, texture);
		}
	}

	return resourceID;
}

shared_ptr<Texture> ResourceManager::FetchTextureByID(const int resourceID) {
	Logger::LogInfo("Loading texture with ID: " + resourceID);

	shared_ptr<Texture> texture;

	auto resourceFinder = _resourceMap.find(resourceID);
	if (resourceFinder != _resourceMap.end()) {
		Logger::LogInfo("Resource found");
		texture = std::dynamic_pointer_cast<Texture>((resourceFinder->second)._resource);
	}
	else {
		Logger::LogError("Failed to find resource by ID");
	}

	return texture;
}


ResourceID ResourceManager::LoadModelByPath(const string& filepath) {
	Logger::LogInfo("Loading Geometry: " + filepath);

	if (!_resourceLoader) {
		Logger::LogError("No resource loader has been set");
		return ResourceID();
	}

	ResourceID resourceID;

	auto it = _pathMap.find(filepath);
	if (it != _pathMap.end()) {
		Logger::LogInfo("Matching path for resource: " + filepath);
		return it->second;
	}
	else {
		// Load new model
		shared_ptr<Geometry> model = _resourceLoader->LoadGeometry(filepath);

		if (model != nullptr) {
			Logger::LogInfo("Adding file to resources: " + filepath);
			int id = GetNewID();
			// Add path to map
			resourceID = ResourceID(ResourceType::Model, id);
			_pathMap[filepath] = resourceID;
			// Add resource to map
			_resourceMap[id] = ResourceData(ResourceType::Model, model);
		}
	}

	return resourceID;
}

shared_ptr<Geometry> ResourceManager::FetchModelByID(const int resourceID) {
	Logger::LogInfo("Loading model with ID: " + resourceID);

	shared_ptr<Geometry> model;

	auto resourceFinder = _resourceMap.find(resourceID);
	if (resourceFinder != _resourceMap.end()) {
		Logger::LogInfo("Resource found");
		model = std::dynamic_pointer_cast<Geometry>((resourceFinder->second)._resource);
	}
	else {
		Logger::LogError("Failed to find resource by ID");
	}

	return model;
}


ResourceID ResourceManager::LoadResourceByPath(const string& filepath, ResourceType resourceType) {
	Logger::LogInfo("Loading resource: " + filepath);

	if (!_resourceLoader) {
		Logger::LogError("No resource loader has been set");
		return ResourceID();
	}

	ResourceID resourceID;

	auto it = _pathMap.find(filepath);
	if (it != _pathMap.end()) {
		Logger::LogInfo("- fetched from _resourceMap");
		return it->second;
	}
	else {
		shared_ptr<IResource> resource = _resourceLoader->LoadResource(filepath);

		if (resource != NULL) {
			Logger::LogInfo("Adding file to resources: " + filepath);
			int id = GetNewID();
			// Add path to map
			resourceID = ResourceID(resourceType, id);
			_pathMap[filepath] = resourceID;
			// Add resource to map
			_resourceMap[id] = ResourceData(resourceType, resource);
		}
	}
	return resourceID;
}

shared_ptr<IResource> ResourceManager::FetchResourceByID(const int resourceID) {
	Logger::LogInfo("Loading resource with ID: " + resourceID);

	shared_ptr<IResource> resource;

	auto resourceFinder = _resourceMap.find(resourceID);
	if (resourceFinder != _resourceMap.end()) {
		Logger::LogInfo("Resource found");
		resource = (resourceFinder->second)._resource;
	}
	else {
		Logger::LogError("Failed to find resource by ID");
	}

	return resource;
}


void ResourceManager::ClearResources() {
	Logger::LogInfo("Clearing Resources");

	// Delete IDs
	for (auto itr = _pathMap.begin();
		itr != _pathMap.end();
		itr++) {

		_pathMap.erase(itr);
	}
	// Delete Resource Data
	for (auto itr = _resourceMap.begin();
		itr != _resourceMap.end();
		itr++)
	{
		//for all the elements of the map
		_resourceMap.erase(itr);
	}

	// NOTE: ID tracker is not reset to lower the risk of leftover errors
}

void ResourceManager::ClearResourcesByType(ResourceType resourceType) {
	Logger::LogInfo("Deleting resources with type: ");
	for (auto itr = _pathMap.begin();
		itr != _pathMap.end();
		itr++) {

		if (resourceType == itr->second._resourceType) {
			// Delete the resource data
			_resourceMap.erase(itr->second._resourceID);
			// Delete the ID
			_pathMap.erase(itr);
		}
	}
}