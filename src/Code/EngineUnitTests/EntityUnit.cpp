#include "stdafx.h"
#include "CppUnitTest.h"

#include <string>
#include "../Engine/Objects/Entity.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EngineUnitTests
{		
	TEST_CLASS(EntityUnitTests)
	{
	public:
		
		TEST_METHOD(CreateEntity)
		{
			// TODO: Your test code here
			const std::string* name =  new std::string("test");
			Entity* entity = new Entity("test");
			Assert::AreEqual(name, entity->GetID());
		}

	};
}