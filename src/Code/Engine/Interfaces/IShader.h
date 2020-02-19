#pragma once

#include <string>
#include "IBufferID.h"

using std::string;

namespace EngineECS {
	enum class ShaderType {
		VertexShader,
		FragmentShader,
		PixelShader,
		GeometryShader,
		TessellationShader,
		PrimitiveShader,
		ComputeShader,
		OtherShader
	};

	class IShader {
	private:

	public:
		virtual ~IShader() = 0;

		virtual bool Initialise() = 0;
		virtual IBufferID* LoadShader(const string& filename, const ShaderType shaderType) = 0;
		virtual void Unload() = 0;
	};
}