#pragma once

#include "pch.h"
#include "CppUnitTest.h"
#include "Objects/Texture.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineECS;

namespace EngineUnitTests
{
	namespace Objects {
		TEST_CLASS(TextureTest) {
		public:

			TEST_METHOD(CreateATexture) {
				// Create texture
				Texture texture = Texture(0);

			}

			//TEST_METHOD(GetBufferID)

			//TEST_METHOD(GetWidth)

			//TEST_METHOD(GetHeight)
		};
	}
}
