#pragma once

#include "pch.h"
#include "CppUnitTest.h"
#include "Objects/Geometry.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineECS;

namespace EngineUnitTests
{
	namespace Objects {
		TEST_CLASS(GeometryTest) {
		public:

			TEST_METHOD(CreateTheCamera) {
				// Create camera
				Geometry geom = Geometry();

			}

			//TEST_METHOD(VerticesCorrect)

			//TEST_METHOD(NormalsCorrect)

			//TEST_METHOD(UVsCorrect)

			//TEST_METHOD(BiNormalCorrect)

			//TEST_METHOD(TangentCorrect)

			//TEST_METHOD(TrianglesCorrect)
		};
	}
}
