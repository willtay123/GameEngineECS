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

			TEST_METHOD(GetInstance) {
				std::unique_ptr<Entity> entity(new Entity("testEntity"));

				// Add an entity to 1 instance
				EntityManager em = EntityManager::GetInstance();
				em.AddEntity("test", std::move(entity));
				// Second instance should have the entity
				EntityManager em2 = EntityManager::GetInstance();

				// Get the number of entities in each instance
				int entCount1 = em.GetEntityCount("test");
				int entCount2 = em.GetEntityCount("test");

				Assert::AreEqual(entCount1, entCount2, L"Instance not fetched correctly");
			}

			TEST_METHOD(AddingAnEntity) {
				//string t = string("test");
				//Entity* entity = new Entity(&t);
				//EntityManager::AddEntity("testList", entity);
				//vector<Entity*> entities = *(EntityManager::GetEntities());
				//Entity* entityBack = entities[0];
				//
				////Assert::AreSame(entityBack, entity); //Doesnt work because it's a custom class
				//EntityManager::ClearEntities("testList");
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
