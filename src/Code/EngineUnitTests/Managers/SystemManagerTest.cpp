#pragma once

#include "pch.h"
#include "CppUnitTest.h"
#include "Managers/SystemManager.h"
#include "TestData/Implementations/System.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineECS;

namespace EngineUnitTests
{
	namespace Managers {
		TEST_CLASS(SystemManagerTest) {
		public:

			TEST_METHOD(AddingAnUpdateSystem) {
				System* system = new System();
				SystemManager::GetInstance().AddUpdateSystem(system);

				const vector<ISystem*>* systems = SystemManager::GetInstance().GetUpdateSystems();
				Assert::IsNotNull((*systems)[0], L"System Manager failed to add an update system");
				SystemManager::GetInstance().ClearUpdateSystems();
			}

			TEST_METHOD(AddingARenderSystem) {
				System* system = new System();
				SystemManager::GetInstance().AddRenderSystem(system);

				const vector<ISystem*>* systems = SystemManager::GetInstance().GetRenderSystems();
				Assert::IsNotNull((*systems)[0], L"System Manager failed to add a render system");
				SystemManager::GetInstance().ClearRenderSystems();
			}

			TEST_METHOD(AddingMultipleUpdateSystems) {
				for (int i = 0; i < 5; i++) {
					System* system = new System();
					SystemManager::GetInstance().AddUpdateSystem(system);
				}

				const vector<ISystem*>* systems = SystemManager::GetInstance().GetUpdateSystems();
				Assert::IsTrue(systems->size() == 5, L"System Manager failed to add multiple update systems");
				SystemManager::GetInstance().ClearUpdateSystems();
			}

			TEST_METHOD(AddingMultipleRenderSystems) {
				for (int i = 0; i < 5; i++) {
					System* system = new System();
					SystemManager::GetInstance().AddRenderSystem(system);
				}

				const vector<ISystem*>* systems = SystemManager::GetInstance().GetRenderSystems();
				Assert::IsTrue(systems->size() == 5, L"System Manager failed to add multiple render systems");
				SystemManager::GetInstance().ClearRenderSystems();
			}

			//TEST_METHOD(ActionUpdateSystem)

			//TEST_METHOD(ActionRenderSystem)
		};
	}
}
