#include "pch.h"
#include "CppUnitTest.h"
#include "Managers/SceneManager.h"
#include "Interfaces/IScene.h"
#include "CleverPointers.h"
#include "TestData/Implementations/Scene.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineECS;

namespace EngineUnitTests
{
	namespace Managers {
		TEST_CLASS(SceneManagerTest) {
		public:

			TEST_METHOD(AddAScene) {
				SceneManager::GetInstance().ClearScenes();
				unique_ptr<IScene> scene = make_unique<Scene>("scene");
				SceneManager::GetInstance().AddScene(std::move(scene));

				int count = SceneManager::GetInstance().GetSceneCount();

				Assert::IsTrue(count == 1, L"Failed to add the scene");
			}

			TEST_METHOD(RemoveAScene) {
				SceneManager::GetInstance().ClearScenes();
				unique_ptr<IScene> scene = make_unique<Scene>("scene");
				SceneManager::GetInstance().AddScene(std::move(scene));

				int beforeCount = SceneManager::GetInstance().GetSceneCount();
				SceneManager::GetInstance().RemoveScene();
				int afterCount = SceneManager::GetInstance().GetSceneCount();

				Assert::IsTrue(beforeCount == 1 && afterCount == 0, L"Failed to remove the scene");
			}

			TEST_METHOD(SwapScene) {
				SceneManager::GetInstance().ClearScenes();
				unique_ptr<IScene> scene = make_unique<Scene>("scene");
				SceneManager::GetInstance().AddScene(std::move(scene));

				unique_ptr<IScene> scene2 = make_unique<Scene>("replacer");
				SceneManager::GetInstance().SwapScene(std::move(scene2));

				string sceneID = SceneManager::GetInstance().GetCurrentSceneID();

				Assert::IsTrue(sceneID == "replacer", L"Failed to swap the current scene");
			}

			TEST_METHOD(GetSceneCount) {
				SceneManager::GetInstance().ClearScenes();
				unique_ptr<IScene> scene = make_unique<Scene>("scene");
				SceneManager::GetInstance().AddScene(std::move(scene));

				int count = SceneManager::GetInstance().GetSceneCount();
				
				wstring info = wstring(L"Scene count was incorrect, returned value is: " + to_wstring(count));
				Assert::IsTrue(count == 1, info.c_str());
			}

			TEST_METHOD(GetCurrentSceneID) {
				SceneManager::GetInstance().ClearScenes();
				unique_ptr<IScene> scene = make_unique<Scene>("scene");
				SceneManager::GetInstance().AddScene(std::move(scene));

				string sceneID = SceneManager::GetInstance().GetCurrentSceneID();

				Assert::IsTrue(sceneID == "scene", L"Failed to get the scene ID");
			}

			TEST_METHOD(ClearScenes) {
				SceneManager::GetInstance().ClearScenes();
				unique_ptr<IScene> scene = make_unique<Scene>("scene");
				SceneManager::GetInstance().AddScene(std::move(scene));

				int beforeCount = SceneManager::GetInstance().GetSceneCount();
				SceneManager::GetInstance().ClearScenes();
				int afterCount = SceneManager::GetInstance().GetSceneCount();

				Assert::IsTrue(beforeCount == 1 && afterCount == 0, L"Failed to clear the scenes");
			}
		};
	}
}
