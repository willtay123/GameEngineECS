#pragma once

#include "IBufferID.h"

namespace EngineECS {
	enum ShaderType {
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

		virtual bool Initialise() = 0;
		virtual IBufferID* LoadShader(const char* filename, ShaderType shaderType) = 0;
		virtual void Unload() = 0;
	};
}