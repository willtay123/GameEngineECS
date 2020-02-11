#pragma once
#include "Interfaces/IExternalLogger.h"

using namespace EngineECS;

class ExternalLogger : public IExternalLogger {
private:

public:
	void WriteLog(LogMessage& logMessage);
};