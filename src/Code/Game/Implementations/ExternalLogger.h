#pragma once
#include "Interfaces/IExternalLogger.h"

using namespace EngineECS;

class ExternalLogger : public IExternalLogger {
private:

public:
	~ExternalLogger();
	void WriteLog(LogMessage& logMessage);
};