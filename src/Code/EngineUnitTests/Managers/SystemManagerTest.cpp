#pragma once

#include "pch.h"
#include "CppUnitTest.h"
#include "Managers/SystemManager.h"
#include "TestObjects/Implementations/System.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineECS;

namespace EngineUnitTests
{
	TEST_CLASS(SystemManagerTest) {
	public:

		TEST_METHOD(AddingAnUpdateSystem) {
			System* system = new System();
			SystemManager::AddUpdateSystem(system);

			const vector<ISystem*>* systems = SystemManager::GetUpdateSystems();
			Assert::IsNotNull((*systems)[0]);
		}

		TEST_METHOD(AddingARenderSystem) {
			System* system = new System();
			SystemManager::AddRenderSystem(system);

			const vector<ISystem*>* systems = SystemManager::GetRenderSystems();
			Assert::IsNotNull((*systems)[0]);
		}
	};
}
