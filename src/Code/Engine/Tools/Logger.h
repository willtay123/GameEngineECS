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
		static Logger* _instance;
		Logger();
		~Logger();

		IExternalLogger* _externalLogger;
		LoggingDestination _loggingDestination;
		unsigned int _logIndex; // Used to order the messages
		unsigned int _maxLogCount;
		queue<LogMessage> _logs;

		void Log(LogMessage& logMessage);
		void WriteLog();

	public:
		static Logger* GetInstance();

		void LogInfo(const char* message);
		void LogInfo(string& message);

		void LogWarning(const char* message);
		void LogWarning(string& message);
		
		void LogError(const char* message);
		void LogError(string& message);

		void SetLoggingDestination(LoggingDestination loggingDestination);
		void SetExternalLogger(IExternalLogger* externalLogger);
	};
}

