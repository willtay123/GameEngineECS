#pragma once

#include <string>
#include <queue>
#include <iostream>
#include "DataStructs/LogMessage.h"
#include <Interfaces\IExternalLogger.h>

using std::string;
using std::queue;

namespace EngineECS {

	const unsigned int MAX_LOG_COUNT = 50;

	enum class LoggingDestination {
		Console,
		File,
		External // If mode changes to external and link is broken, default to console
	};

	class Logger {
	private:
		Logger();
		~Logger();

		static IExternalLogger* _externalLogger;
		static LoggingDestination _loggingDestination;
		static unsigned int _logIndex; // Used to order the messages
		static unsigned int _maxLogCount;
		static queue<LogMessage> _logs;

		static void Log(LogMessage& logMessage);
		static void WriteLog();

	public:
		static void LogInfo(const char* message);
		static void LogInfo(string& message);

		static void LogWarning(const char* message);
		static void LogWarning(string& message);
		
		static void LogError(const char* message);
		static void LogError(string& message);

		static void SetLoggingDestination(LoggingDestination loggingDestination);
		static void SetExternalLogger(IExternalLogger* externalLogger);
	};
}

