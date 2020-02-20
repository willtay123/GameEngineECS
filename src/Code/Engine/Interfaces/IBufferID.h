#pragma once


namespace EngineECS {
	class IBufferID {
	private:

	public:
		virtual ~IBufferID() {}

		virtual const char* GetName() = 0;
	};
}