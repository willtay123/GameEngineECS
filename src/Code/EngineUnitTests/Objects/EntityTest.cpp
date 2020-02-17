#pragma once

#include "pch.h"
#include "CppUnitTest.h"
#include "Objects/Entity.h"
#include <Components\ComponentTransform.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineECS;

namespace EngineUnitTests
{
	namespace Objects {
		TEST_CLASS(EntityTest) {
		public:

			TEST_METHOD(CreateAnEntity) {
				// Create entity
				Entity* entity = new Entity("Test");

				// Check entity has its data set
				const string* id = entity->GetID();
				Assert::IsTrue(*id == "Test");

				// Cleanup
				delete entity;
			}

			TEST_METHOD(AddComponentToEntity) {
				// Create data
				Entity* entity = new Entity("Test");
				ComponentTransform* comp = new ComponentTransform();
				entity->AddComponent(comp);

				// Check if entity had a component added
				const vector<IComponent*>* components = entity->GetComponents();
				Assert::IsTrue(components->size() > 0);

				// Cleanup
				delete entity;
			}
		};
	}
}
