#pragma once

#include <windows.h>
#include <deque>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "DataStructs/LogMessage.h"
#include "Interfaces/IExternalLogger.h"

using std::deque;
using std::vector;
using std::string;
using std::ofstream;

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
		static deque<LogMessage> _logs;
		static ofstream _logFile;
		static const char* LOG_FILEPATH;

		static void Log(LogMessage& logMessage);
		static void WriteLog();
		static void WriteLogToFile(EngineECS::LogMessage& message);


	public:
		static void LogInfo(const char* message);
		static void LogInfo(const char* tag, const char* message);
		static void LogInfo(string& message);
		static void LogInfo(string& tag, string& message);

		static void LogWarning(const char* message);
		static void LogWarning(const char* tag, const char* message);
		static void LogWarning(string& message);
		static void LogWarning(string& tag, string& message);

		static void LogError(const char* message);
		static void LogError(const char* tag, const char* message);
		static void LogError(string& message);
		static void LogError(string& tag, string& message);

		static void GetLogs(vector<LogMessage>& logs);
		static void GetLogsByTag(string& tag, vector<LogMessage>& logs);

		static void SetLogCountLimit(unsigned int limit);

		static void SetLoggingDestination(LoggingDestination loggingDestination);
		static LoggingDestination GetLoggingDestination() { return _loggingDestination; }

		static void SetExternalLogger(IExternalLogger* externalLogger);
		static IExternalLogger* GetExternalLogger() { return _externalLogger; }
	};
}
