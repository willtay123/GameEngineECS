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

			TEST_METHOD(GetView) {
				Camera camera;

				camera.LookAt(vec3(0, 0, 1), vec3(0, 1, 0));
				camera.Update(0.0f);
				mat4 view = camera.GetView();
				mat4 compare = glm::lookAt(vec3(0,0,0), vec3(0,0,1), vec3(0,1,0));

				Assert::IsTrue(view == compare, L"failed to get the view matrix");
			}

			TEST_METHOD(GetProjection) {
				Camera camera;

				mat4 proj = camera.GetProjection();

				mat4 projection = glm::perspective(
					(float)glm::radians(80.0f),
					1280.0f / 780.0f,
					1.0f,
					50.0f
				);

				Assert::IsTrue(proj == projection, L"Failed to get the projection matrix");
			}

			TEST_METHOD(Rotate90DegreesLeft) {
				Camera camera;

				camera.LookAt(vec3(0, 0, 1), vec3(0, 1, 0));
				camera.TurnOnAxis(-90, vec3(0, 1, 0));

				mat4 newLook = camera.GetView();
				mat4 compare = glm::lookAt(vec3(0, 0, 0), vec3(-1, 0, 0), vec3(0, 1, 0));

				Assert::IsTrue(newLook == compare, L"Failed to rotate 90 degrees left");
			}

			TEST_METHOD(Rotate90DegreesRight) {
				Camera camera;

				camera.LookAt(vec3(0, 0, 1), vec3(0, 1, 0));
				camera.TurnOnAxis(90, vec3(0, 1, 0));

				mat4 newLook = camera.GetView();
				mat4 compare = glm::lookAt(vec3(0, 0, 0), vec3(1, 0, 0), vec3(0, 1, 0));

				Assert::IsTrue(newLook == compare, L"Failed to rotate 90 degrees left");
			}

			TEST_METHOD(LookDown) {
				Camera camera;

				camera.LookAt(vec3(0, 0, 1), vec3(0, 1, 0));
				camera.TurnOnAxis(90, vec3(1, 0, 0));

				mat4 newLook = camera.GetView();
				mat4 compare = glm::lookAt(vec3(0, 0, 0), vec3(0, -1, 0), vec3(0, 0, 1));

				Assert::IsTrue(newLook == compare, L"Failed to rotate 90 degrees left");
			}
		};
	}
}
