#pragma once

#include "pch.h"
#include "CppUnitTest.h"
#include "Managers/SystemManager.h"
#include "TestObjects/Implementations/System.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineECS;

namespace EngineUnitTests
{
	namespace Managers {
		TEST_CLASS(SystemManagerTest) {
		public:

			TEST_METHOD(AddingAnUpdateSystem) {
				System* system = new System();
				SystemManager::AddUpdateSystem(system);

				const vector<ISystem*>* systems = SystemManager::GetUpdateSystems();
				Assert::IsNotNull((*systems)[0], L"System Manager failed to add an update system");
				SystemManager::ClearUpdateSystems();
			}

			TEST_METHOD(AddingARenderSystem) {
				System* system = new System();
				SystemManager::AddRenderSystem(system);

				const vector<ISystem*>* systems = SystemManager::GetRenderSystems();
				Assert::IsNotNull((*systems)[0], L"System Manager failed to add a render system");
				SystemManager::ClearRenderSystems();
			}

			TEST_METHOD(AddingMultipleUpdateSystems) {
				for (int i = 0; i < 5; i++) {
					System* system = new System();
					SystemManager::AddUpdateSystem(system);
				}

				const vector<ISystem*>* systems = SystemManager::GetUpdateSystems();
				Assert::IsTrue(systems->size() == 5, L"System Manager failed to add multiple update systems");
				SystemManager::ClearUpdateSystems();
			}

			TEST_METHOD(AddingMultipleRenderSystems) {
				for (int i = 0; i < 5; i++) {
					System* system = new System();
					SystemManager::AddRenderSystem(system);
				}

				const vector<ISystem*>* systems = SystemManager::GetRenderSystems();
				Assert::IsTrue(systems->size() == 5, L"System Manager failed to add multiple render systems");
				SystemManager::ClearRenderSystems();
			}
		};
	}
}
