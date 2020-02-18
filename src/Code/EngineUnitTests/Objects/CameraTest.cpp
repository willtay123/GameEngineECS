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
				Camera camera;

				vec3 position = camera.GetPosition();
				vec3 direction = camera.GetDirection();
				vec3 up = camera.GetUp();

				vec3 p(0, 0, 0);
				vec3 d(1, 0, 0);
				vec3 u(0, 1, 0);

				Assert::IsTrue(
					(position == p && direction == d && up == u),
					L"Camera creation failed to create member data"
				);
			}

			TEST_METHOD(SetPosition) {
				Camera camera;

				vec3 position(1, 2, 3);
				camera.SetPosition(position);

				vec3 posBack = camera.GetPosition();

				Assert::IsTrue(
					(position == posBack),
					L"Camera failed to set position"
				);
			}

			TEST_METHOD(SetDirection) {
				Camera camera;

				vec3 direction(2, 0, 0);
				camera.SetDirection(direction);

				vec3 directionBack = camera.GetDirection();

				Assert::IsTrue(
					(directionBack == vec3(1,0,0)),
					L"Camera failed to set direction"
				);
			}

			TEST_METHOD(SetUp) {
				Camera camera;

				vec3 up(0, 2, 0);
				camera.SetUp(up);

				vec3 upBack = camera.GetUp();

				Assert::IsTrue(
					(upBack == vec3(0,1,0)),
					L"Camera failed to set position"
				);
			}

			//TEST_METHOD(GetView)

			//TEST_METHOD(GetProjection)

			//TEST_METHOD(Rotate90DegreesLeft)

			//TEST_METHOD(Rotate90DegreesRight)

			//TEST_METHOD(LookDown)
		};
	}
}
