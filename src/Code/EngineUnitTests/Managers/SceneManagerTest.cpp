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
				unique_ptr<IScene> scene = make_unique<Scene>("scene");
				SceneManager::GetInstance().AddScene(std::move(scene));

				int count = SceneManager::GetInstance().GetSceneCount();

				Assert::IsTrue(count == 1, L"Failed to add the scene");
			}

			//TEST_METHOD(RemoveAScene)

			//TEST_METHOD(SwapScene)

			//TEST_METHOD(GetSceneCount)

			//TEST_METHOD(GetCurrentSceneID)
		};
	}
}
