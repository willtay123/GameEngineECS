#include "pch.h"
#include "CppUnitTest.h"
#include "Managers/ResourceManager.h"
#include "Interfaces/IResource.h"
#include "CleverPointers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineECS;

namespace EngineUnitTests
{
	namespace Managers {
		TEST_CLASS(ResourceManagerTest) {
		public:

			TEST_METHOD(LoadTexture) {
				//ResourceManager::GetInstance().SetResourceLoader(new ResourceLoader());
				shared_ptr<Texture> texture = ResourceManager::GetInstance().LoadTexture("TestData/Assets/testImage.png");

				Assert::IsTrue(texture != nullptr, L"Failed to load texture");
			}

			TEST_METHOD(ClearTextures) {
				int sizeBefore = ResourceManager::GetInstance().GetTextureCount();
				ResourceManager::GetInstance().ClearTextures();
				int sizeAfter = ResourceManager::GetInstance().GetTextureCount();

				Assert::IsTrue(sizeBefore == 1 && sizeAfter == 0, L"Failed to clear textures");
			}

			TEST_METHOD(LoadGeometry) {
				//ResourceManager::GetInstance().SetResourceLoader(new ResourceLoader());
				shared_ptr<Geometry> model = ResourceManager::GetInstance().LoadModel("TestData/Assets/testModel.obj");

				Assert::IsTrue(model != nullptr, L"Failed to load texture");
			}

			TEST_METHOD(ClearGeometry) {
				int sizeBefore = ResourceManager::GetInstance().GetModelCount();
				ResourceManager::GetInstance().ClearModels();
				int sizeAfter = ResourceManager::GetInstance().GetModelCount();

				Assert::IsTrue(sizeBefore == 1 && sizeAfter == 0, L"Failed to clear models");
			}

			TEST_METHOD(LoadResource) {
				//ResourceManager::GetInstance().SetResourceLoader(new ResourceLoader());
				shared_ptr<IResource> resource = ResourceManager::GetInstance().LoadResource("TestData/Assets/testResource.png");

				Assert::IsTrue(resource != nullptr, L"Failed to load texture");
			}

			TEST_METHOD(ClearResources) {
				int sizeBefore = ResourceManager::GetInstance().GetResourceCount();
				ResourceManager::GetInstance().ClearResources();
				int sizeAfter = ResourceManager::GetInstance().GetResourceCount();

				Assert::IsTrue(sizeBefore == 1 && sizeAfter == 0, L"Failed to clear resources");
			}
		};
	}
}
