#pragma once


namespace EngineECS {
	class IBufferID {
	private:

	public:
		virtual ~IBufferID() = 0;

		virtual const char* GetName() = 0;
	};
}