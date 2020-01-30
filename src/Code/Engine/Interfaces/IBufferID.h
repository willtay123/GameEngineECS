#pragma once


namespace EngineECS {
	class IBufferID {
	private:

	public:
		virtual const char* GetName() = 0;
	};
}