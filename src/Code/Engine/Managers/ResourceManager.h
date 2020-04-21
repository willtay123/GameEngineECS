#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>

#include "Interfaces/IResourceLoader.h"
#include "Interfaces/IResource.h"
#include "Objects/Texture.h"
#include "Objects/Geometry.h"
#include "Tools/Logger.h"
#include "CleverPointers.h"
#include "DataStructs/ResourceTypes.h"
#include "DataStructs/ResourceID.h"
#include "DataStructs/ResourceData.h"

using std::unordered_map;
using std::make_pair;
using std::string;

namespace EngineECS {

	class ResourceManager {
	private:
		typedef unordered_map<string, ResourceID> PathMap;
		typedef unordered_map<int, ResourceData> ResourceMap;

		static ResourceManager* Instance;
		IResourceLoader* _resourceLoader;

		unsigned int _idTracker;
		PathMap _pathMap;
		ResourceMap _resourceMap;
		
		ResourceManager();

		unsigned int GetNewID() { return _idTracker++; }

	public:
		~ResourceManager();
		static ResourceManager& GetInstance();

		void SetResourceLoader(IResourceLoader* _resourceLoader);
		IResourceLoader* GetResourceLoader() const { return _resourceLoader; }

		ResourceID LoadTextureByPath(const string& filepath);
		shared_ptr<Texture> FetchTextureByID(const int resourceID);

		ResourceID LoadModelByPath(const string& filepath);
		shared_ptr<Geometry> FetchModelByID(const int resourceID);

		ResourceID LoadResourceByPath(const string& filepath, ResourceType resourceType);
		shared_ptr<IResource> FetchResourceByID(const int resourceID);

		void ClearResources();
		void ClearResourcesByType(ResourceType resourceType);

		int GetResourceCount() const { return _resourceMap.size(); }
	};
}