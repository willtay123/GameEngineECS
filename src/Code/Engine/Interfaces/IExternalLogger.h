#pragma once
#include "DataStructs/LogMessage.h"


namespace EngineECS {
	class IExternalLogger {
	public:
		virtual ~IExternalLogger() = 0;

		virtual void WriteLog(LogMessage& message) = 0;
	};
}