#include "pch.h"
#include "CppUnitTest.h"
#include "Managers/CollisionManager.h"
#include "Interfaces/ICollisionManifold.h"
#include "TestObjects/Implementations/CollisionDetector.h"
#include "TestObjects/Implementations/CollisionResponder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineECS;

namespace EngineUnitTests
{
	namespace Managers {
		TEST_CLASS(CollisionManagerTest) {
		public:

			TEST_METHOD(DetectCollisions) {
				CollisionManager::GetInstance().SetCollisionDetector(new CollisionDetector());
				CollisionManager::GetInstance().SetCollisionResponder(new CollisionResponder());
				shared_ptr<EntityList> el = make_shared<EntityList>("testList");

				shared_ptr<Entity> entity1 = make_shared<Entity>("testEntity1");
				//entity1->AddComponent(new ComponentTransform());
				//entity1->AddComponent(new ComponentSphereCollider());

				shared_ptr<Entity> entity2 = make_shared<Entity>("testEntity1");
				//entity2->AddComponent(new ComponentTransform());
				//entity2->AddComponent(new ComponentSphereCollider());

				CollisionManager::GetInstance().DetectCollisions(el);
				const vector<ICollisionManifold*> collisions = CollisionManager::GetInstance().GetCollisions();

				Assert::IsTrue(collisions.size() == 1, L"Failed to detect collisions");
			}

			//TEST_METHOD(HandleCollisions)

			//TEST_METHOD(ClearCollisions)
		};
	}
}
