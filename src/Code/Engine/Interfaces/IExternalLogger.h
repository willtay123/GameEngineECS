#pragma once
#include "DataStructs/LogMessage.h"


namespace EngineECS {
	class IExternalLogger {
	public:
		virtual void WriteLog(LogMessage& message) = 0;
	};
}