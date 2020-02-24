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
				std::unique_ptr<Entity> entity(new Entity("test"));
				EntityManager::GetInstance().AddEntity("testList", std::move(entity));
				std::shared_ptr<EntityList> entities = EntityManager::GetInstance().GetEntities().lock();
				std::shared_ptr<Entity> entityBack = (*entities)[0].lock();
				
				Assert::IsTrue((*entityBack) == (*entity), L"Failed to add entity");
				EntityManager::GetInstance().ClearEntityGroup("testList");
			}

			TEST_METHOD(RemoveAnEntity) {
				std::unique_ptr<Entity> entity(new Entity("testEntity"));
				// Ensure it is added
				EntityManager::GetInstance().AddEntity("testList", std::move(entity));
				bool added = (EntityManager::GetInstance().GetEntityCount("testList") > 0);

				// Ensure it is removed
				EntityManager::GetInstance().RemoveEntity("testList", "testEntity");
				bool removed = (EntityManager::GetInstance().GetEntityCount("testList") == 0);

				Assert::IsTrue(added && removed, L"Failed to remove entity");
			}

			//TEST_METHOD(GetNonEditableEntities)

			//TEST_METHOD(GetEditableEntities)

			//TEST_METHOD(GetNonEditableEntity)

			//TEST_METHOD(GetEditableEntity)

			TEST_METHOD(SwapEntityGroup) {
				std::unique_ptr<Entity> entity1(new Entity("testEntity1"));
				std::unique_ptr<Entity> entity2(new Entity("testEntity2"));
				EntityManager::GetInstance().AddEntity("testList1", std::move(entity1));
				EntityManager::GetInstance().AddEntity("testList2", std::move(entity2));

				std::shared_ptr<EntityList> entities1 = EntityManager::GetInstance().GetEntities().lock();
				EntityManager::GetInstance().SetActiveEntityGroup("testList2");
				std::shared_ptr<EntityList> entities2 = EntityManager::GetInstance().GetEntities().lock();

				Assert::IsTrue(entities1 == entities2, L"Failed to swap entity list");
			}
		};
	}
}
