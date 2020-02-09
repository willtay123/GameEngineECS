#pragma once

#include <string>
#include <queue>

using std::string;
using std::queue;

namespace EngineECS {
	enum class LoggingDestination {
		Console,
		File,
		External // If mode changes to external and link is broken, default to console
	};

	enum class LogLevel {
		Info,
		Warning,
		Error
	};

	struct LogMessage {
		LogLevel _logLevel;
		string _message;

		LogMessage(LogLevel logLevel, string message) :
			_logLevel(logLevel),
			_message(message) {
		}
	};

	class Logger {
	private:
		static Logger* _instance;
		Logger();
		~Logger();

		LoggingDestination _loggingDestination;
		int _logIndex; // Used to order the messages
		int _maxLogCount;
		queue<LogMessage> _logs;

		void Log(LogMessage& logMessage);

	public:
		static Logger* GetInstance();

		void LogInfo(string& message);
		void LogWarning(string& message);
		void LogError(string& message);
	};
}

