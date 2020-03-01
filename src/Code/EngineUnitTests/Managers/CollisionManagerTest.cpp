#include "pch.h"
#include "CppUnitTest.h"
#include "Managers/CollisionManager.h"
#include "Interfaces/ICollisionManifold.h"
#include "TestData/Implementations/CollisionDetector.h"
#include "TestData/Implementations/CollisionResponder.h"
#include "Components/ComponentTransform.h"

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
				entity1->AddComponent(new ComponentTransform(0, 0, 0));
				//entity1->AddComponent(new ComponentSphereCollider(2));

				shared_ptr<Entity> entity2 = make_shared<Entity>("testEntity1");
				entity2->AddComponent(new ComponentTransform(0, 0, 0));
				//entity2->AddComponent(new ComponentSphereCollider(3));

				CollisionManager::GetInstance().DetectCollisions(el);
				const vector<ICollisionManifold*> collisions = CollisionManager::GetInstance().GetCollisions();

				Assert::IsTrue(collisions.size() == 1, L"Failed to detect collisions");
			}

			//TEST_METHOD(HandleCollisions)

			//TEST_METHOD(ClearCollisions)
		};
	}
}
