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
				string listID = "testList";

				std::shared_ptr<Entity> entity = std::make_shared<Entity>("testEntity");

				// Add an entity to 1 instance
				EntityManager em = EntityManager::GetInstance();
				em.AddEntity(listID, entity);
				// Second instance should have the entity
				EntityManager em2 = EntityManager::GetInstance();

				// Get the number of entities in each instance
				int entCount1 = em.GetEntityCount(listID);
				int entCount2 = em.GetEntityCount(listID);

				Assert::AreEqual(entCount1, entCount2, L"Instance not fetched correctly");
				EntityManager::GetInstance().ClearAllEntities();
			}

			TEST_METHOD(AddingAnEntity) {
				std::shared_ptr<Entity> entity = std::make_shared<Entity>("test");
				EntityManager::GetInstance().AddEntity("testList", entity);
				std::shared_ptr<const EntityList> entities = EntityManager::GetInstance().GetEntities().lock();
				std::shared_ptr<Entity> entityBack = (*entities)[0].lock();
				
				Assert::IsTrue((*entityBack) == (*entity), L"Failed to add entity");
				EntityManager::GetInstance().ClearAllEntities();
			}

			TEST_METHOD(RemoveAnEntity) {
				string listID = "testList";
				string entityID = "testEntity";

				std::shared_ptr<Entity> entity = std::make_shared<Entity>(entityID);
				EntityManager::GetInstance().AddEntity(listID, entity);
				// Ensure it is added
				bool added = (EntityManager::GetInstance().GetEntityCount(listID) > 0);

				EntityManager::GetInstance().RemoveEntity(listID, entityID);
				EntityManager::GetInstance().EnactRemovals();
				// Ensure it is removed
				bool removed = (EntityManager::GetInstance().GetEntityCount(listID) == 0);

				Assert::IsTrue(added && removed, L"Failed to remove entity");
				EntityManager::GetInstance().ClearAllEntities();
			}

			TEST_METHOD(GetNonEditableEntities) {
				string listID = "testList";
				string entityID = "testEntity";

				std::shared_ptr<Entity> entity = std::make_shared<Entity>(entityID);
				EntityManager::GetInstance().AddEntity(listID, entity);
				std::shared_ptr<const EntityList> entityList = EntityManager::GetInstance().GetEntities().lock();

				Assert::IsTrue(entityList->size() > 0, L"Failed to get const entities");
				EntityManager::GetInstance().ClearAllEntities();
			}

			TEST_METHOD(GetEditableEntities) {
				string listID = "testList";
				string entityID = "testEntity";

				std::shared_ptr<Entity> entity = std::make_shared<Entity>(entityID);
				EntityManager::GetInstance().AddEntity(listID, entity);
				std::shared_ptr<EntityList> entityList = EntityManager::GetInstance().GetEntitiesEditable().lock();

				Assert::IsTrue(entityList->size() > 0, L"Failed to get non-const entities");
				EntityManager::GetInstance().ClearAllEntities();
			}

			TEST_METHOD(GetNonEditableEntity) {
				string listID = "testList";
				string entityID = "testEntity";

				std::shared_ptr<Entity> entity = std::make_shared<Entity>(entityID);
				EntityManager::GetInstance().AddEntity(listID, entity);
				std::shared_ptr<const Entity> entityBack = EntityManager::GetInstance().GetEntity(listID, entityID).lock();

				Assert::IsTrue(entityBack != nullptr, L"Failed to get non-editable entity");
				EntityManager::GetInstance().ClearAllEntities();
			}

			TEST_METHOD(GetEditableEntity) {
				string listID = "testList";
				string entityID = "testEntity";

				std::shared_ptr<Entity> entity = std::make_shared<Entity>(entityID);
				EntityManager::GetInstance().AddEntity(listID, entity);
				std::shared_ptr<Entity> entityBack = EntityManager::GetInstance().GetEntityEditable(listID, entityID).lock();

				Assert::IsTrue(entityBack != nullptr, L"Failed to get editable entity");
				EntityManager::GetInstance().ClearAllEntities();
			}

			TEST_METHOD(SwapEntityGroup) {
				string entity1ID = "testEntity1";
				string entity2ID = "testEntity2";
				string list1ID = "testList1";
				string list2ID = "testList2";

				std::shared_ptr<Entity> entity1 = std::make_shared<Entity>(entity1ID);
				std::shared_ptr<Entity> entity2 = std::make_shared<Entity>(entity2ID);
				EntityManager::GetInstance().AddEntity(list1ID, entity1);
				EntityManager::GetInstance().AddEntity(list2ID, entity2);

				std::shared_ptr<const EntityList> entities1 = EntityManager::GetInstance().GetEntities().lock();
				EntityManager::GetInstance().SetActiveEntityGroup(list2ID);
				std::shared_ptr<const EntityList> entities2 = EntityManager::GetInstance().GetEntities().lock();

				// May need to edit this to check each list for the matching entity rather
				// than a not-similar check which can be ambiguous
				Assert::IsTrue(entities1 != entities2, L"Failed to swap entity list");
				EntityManager::GetInstance().ClearAllEntities();
			}
		};
	}
}
