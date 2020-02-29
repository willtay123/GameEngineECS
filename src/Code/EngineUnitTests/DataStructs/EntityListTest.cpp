#include "pch.h"
#include "CppUnitTest.h"
#include "DataStructs/EntityList.h"
#include "Objects/Entity.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineECS;

namespace EngineUnitTests
{
	namespace DataStructs {
		TEST_CLASS(EntityManagerTest) {
		public:

			TEST_METHOD(ConstructEntityList) {
				EntityList el("testList");
				int size = el.size();

				Assert::IsTrue(size == 0, L"Entity List failed construction");
			}

			TEST_METHOD(AddAnEntity) {
				EntityList el("testList");
				el.AddEntity(make_shared<Entity>("testEntity"));
				int size = el.size();

				Assert::IsTrue(size == 1, L"Failed to add an entity");
			}

			TEST_METHOD(RemoveAnEntity) {
				EntityList el("testList");
				el.AddEntity(make_shared<Entity>("testEntity"));
				int addSize = el.size();
				el.RemoveEntity("testEntity");
				int removeSize = el.size();

				Assert::IsTrue((addSize == 1) && (removeSize == 0), L"Failed to remove entity");
			}

			TEST_METHOD(GetByOperatorSquareBrackets) {
				EntityList el("testList");
				el.AddEntity(make_shared<Entity>("testEntity"));
				std::weak_ptr<Entity> entity = el[0];
				string id = entity.lock()->GetID();

				Assert::IsTrue(id == "testEntity", L"Failed to get entity by []");
			}

			TEST_METHOD(DataInstancing) {
				EntityList el1("list1");
				EntityList el2 = el1;

				el1.AddEntity(make_shared<Entity>("testEntity"));
				int list2size = el2.size();

				Assert::IsTrue(list2size == 1, L"EntityList failed instance test");
			}
		};
	}
}
