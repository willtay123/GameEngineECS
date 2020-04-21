#pragma once
#include "pch.h"
#include "CppUnitTest.h"
#include "Managers/ResourceManager.h"
#include "Interfaces/IResource.h"
#include "CleverPointers.h"
#include <Tools/Logger.h>
#include <sstream>

#include "TestData/Implementations/ResourceLoader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineECS;

namespace EngineUnitTests
{
	namespace Managers {
		TEST_CLASS(ResourceManagerTest) {
		public:
			unsigned int _textureID = 0;
			unsigned int _modelID = 0;
			unsigned int _resourceID = 0;


			TEST_METHOD(SetResourceLoader) {
				EngineECS::Logger::SetLoggingDestination(LoggingDestination::File);
				EngineECS::Logger::LogInfo("Test", "SetResourceLoader");

				IResourceLoader* resourceLoader = new ResourceLoader();
				ResourceManager::GetInstance().SetResourceLoader(resourceLoader);
				
				IResourceLoader* returned = ResourceManager::GetInstance().GetResourceLoader();

				Assert::IsTrue(resourceLoader == returned, L"Failed to set the resource loader");
			}

			TEST_METHOD(LoadTexture) {
				EngineECS::Logger::SetLoggingDestination(LoggingDestination::File);
				EngineECS::Logger::LogInfo("Test", "LoadTexture");
				ResourceManager::GetInstance().SetResourceLoader(new ResourceLoader());

				ResourceID textureID = ResourceManager::GetInstance().LoadTextureByPath("TestData/Assets/testImage.png");
				_textureID = textureID._resourceID;
				Assert::IsTrue(textureID._resourceID != 0, L"Failed to load texture");
			}

			TEST_METHOD(LoadGeometry) {
				EngineECS::Logger::SetLoggingDestination(LoggingDestination::File);
				EngineECS::Logger::LogInfo("Test", "LoadModel");
				ResourceManager::GetInstance().SetResourceLoader(new ResourceLoader());

				ResourceID modelID = ResourceManager::GetInstance().LoadModelByPath("TestData/Assets/testCube.obj");
				_modelID = modelID._resourceID;
				Assert::IsTrue(modelID._resourceID != 0, L"Failed to load texture");
			}

			TEST_METHOD(LoadResource) {
				EngineECS::Logger::SetLoggingDestination(LoggingDestination::File);
				EngineECS::Logger::LogInfo("Test", "LoadResource");
				ResourceManager::GetInstance().SetResourceLoader(new ResourceLoader());

				ResourceID resourceID = ResourceManager::GetInstance().LoadResourceByPath("TestData/Assets/testResource.png", ResourceType::Unspecified);
				_resourceID = resourceID._resourceID;
				Assert::IsTrue(resourceID._resourceID != 0, L"Failed to load texture");
			}

			TEST_METHOD(GetResourceCount) { // FAILURE: running before the loading tests, cant force order, test needs load logic added
				EngineECS::Logger::SetLoggingDestination(LoggingDestination::File);
				EngineECS::Logger::LogInfo("Test", "GetResourceCount");

				int resourceCount = ResourceManager::GetInstance().GetResourceCount();
				EngineECS::Logger::LogInfo("Test", "Resource count = " + std::to_string(resourceCount));

				Assert::IsTrue(resourceCount == 3, L"Failed to get resource count");
			}

			TEST_METHOD(ClearTextures) {
				EngineECS::Logger::SetLoggingDestination(LoggingDestination::File);
				EngineECS::Logger::LogInfo("Test", "Clear Textures");
				ResourceManager::GetInstance().SetResourceLoader(new ResourceLoader());
				ResourceID textureID = ResourceManager::GetInstance().LoadTextureByPath("TestData/Assets/testImage.png");

				if (textureID._resourceID == 0) {
					// No need to test if the load failed
					EngineECS::Logger::LogWarning("Test", "Aborted due to failed texture load");
					return;
				}

				ResourceManager::GetInstance().ClearResourcesByType(ResourceType::Texture);
				shared_ptr<Texture> texture = ResourceManager::GetInstance().FetchTextureByID(textureID._resourceID);

				Assert::IsTrue(texture == nullptr, L"Failed to clear textures");
			}

			TEST_METHOD(ClearGeometry) {
				if (_modelID == 0) {
					// No need to test if the load failed
					return;
				}

				ResourceManager::GetInstance().ClearResourcesByType(ResourceType::Model);
				shared_ptr<Geometry> model = ResourceManager::GetInstance().FetchModelByID(_textureID);

				Assert::IsTrue(model != nullptr, L"Failed to clear models");
			}

			TEST_METHOD(ClearResources) {
				if (_resourceID == 0) {
					// No need to test if the load failed
					return;
				}

				ResourceManager::GetInstance().ClearResources();
				shared_ptr<IResource> resource = ResourceManager::GetInstance().FetchResourceByID(_textureID);

				Assert::IsTrue(resource != nullptr, L"Failed to clear resources");
			}
		};
	}
}
