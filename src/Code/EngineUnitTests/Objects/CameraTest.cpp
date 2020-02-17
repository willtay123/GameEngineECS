#pragma once

#include "pch.h"
#include "CppUnitTest.h"
#include "Objects/Camera.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineECS;

namespace EngineUnitTests
{
	namespace Objects {
		TEST_CLASS(CameraTest) {
		public:

			TEST_METHOD(CreateTheCamera) {
				// Create camera
				Camera camera();

				
			}

			//TEST_METHOD(LookAt)

			//TEST_METHOD(Rotate90DegreesLeft)

			//TEST_METHOD(Rotate90DegreesRight)

			//TEST_METHOD(LookDown)
		};
	}
}
