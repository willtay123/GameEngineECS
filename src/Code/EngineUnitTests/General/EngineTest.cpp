#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EngineUnitTests
{
	TEST_CLASS(EngineTest) {
	public:
		
		TEST_METHOD(Test2) {
			std::string name = "Bill";
			std::string name2 = "Bill";
			Assert::AreEqual(name, name2);
		}
	};
}
