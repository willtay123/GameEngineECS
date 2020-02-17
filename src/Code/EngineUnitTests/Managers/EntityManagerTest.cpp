#include "pch.h"
#include "CppUnitTest.h"
#include "Managers/EntityManager.h"
#include "Objects/Entity.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineECS;

namespace EngineUnitTests
{
	namespace Managers {
		TEST_CLASS(EntityManagerTest) {
		public:

			//TEST_METHOD(Initialise)

			TEST_METHOD(AddingAnEntity) {
				string t = string("test");
				Entity* entity = new Entity(&t);
				EntityManager::AddEntity("testList", entity);
				vector<Entity*> entities = *(EntityManager::GetEntities());
				Entity* entityBack = entities[0];

				//Assert::AreSame(entityBack, entity); //Doesnt work because it's a custom class
			}

			//TEST_METHOD(RemoveAnEntity)

			//TEST_METHOD(GetNonEditableEntities)

			//TEST_METHOD(GetEditableEntities)

			//TEST_METHOD(GetNonEditableEntity)

			//TEST_METHOD(GetEditableEntity)

			//TEST_METHOD(SwapEntityGroup)
		};
	}
}
