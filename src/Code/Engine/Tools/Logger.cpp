#include "Logger.h"

using namespace EngineECS;

LoggingDestination Logger::_loggingDestination = LoggingDestination::Console;
unsigned int Logger::_logIndex = 0;
unsigned int Logger::_maxLogCount = MAX_LOG_COUNT;
deque<LogMessage> Logger::_logs = deque<LogMessage>();
IExternalLogger* Logger::_externalLogger = nullptr;

Logger::Logger() {
}

Logger::~Logger() {
	//delete _externalLogger; //Is this meant to be here in singleton
}

void Logger::WriteLog() {
	LogMessage message = _logs.back();

	switch (_loggingDestination) {
	case LoggingDestination::Console:
		if (message._logLevel == LogLevel::Error) {
			std::cout << "ERROR: ";
		}
		std::cout << message._message << std::endl;
		break;
	case LoggingDestination::File:
		// Logic needs planning to avoid file re-opening or lost logs
		break;
	case LoggingDestination::External:
		if (_externalLogger) {
			_externalLogger->WriteLog(message);
		}
		else {
			_loggingDestination = LoggingDestination::Console;
			WriteLog();
			LogError("External logger is NULL, logging destination has been set to console");
		}
		break;
	}
}

void Logger::Log(LogMessage& logMessage) {
	_logs.push_back(logMessage);
	if (_logs.size() > _maxLogCount) {
		_logs.pop_front();
	}
	WriteLog();
	_logIndex++;
}

void Logger::LogInfo(const char* message) {
	string messageAsString = string(message);
	LogInfo(messageAsString);
}

void Logger::LogInfo(string& message) {
	string tag = string("");
	Logger::LogInfo(tag, message);
}

void Logger::LogInfo(string& tag, string& message) {
	LogMessage logMessage = LogMessage(LogLevel::Info, _logIndex, tag, message);
	Log(logMessage);
}

void Logger::LogWarning(const char* message) {
	string messageAsString = string(message);
	LogWarning(messageAsString);
}

void Logger::LogWarning(string& message) {
	string tag = string("");
	Logger::LogWarning(tag, message);
}

void Logger::LogWarning(string& tag, string& message) {
	LogMessage logMessage = LogMessage(LogLevel::Warning, _logIndex, tag, message);
	Log(logMessage);
}

void Logger::LogError(const char* message) {
	string messageAsString = string(message);
	LogError(messageAsString);
}

void Logger::LogError(string& message) {
	string tag = string("");
	Logger::LogError(tag, message);
}

void Logger::LogError(string& tag, string& message) {
	LogMessage logMessage = LogMessage(LogLevel::Error, _logIndex, tag, message);
	Log(logMessage);
}

void Logger::GetLogs(vector<LogMessage>& logs) {
	for (size_t i = 0; i < _logs.size(); i++) {
		logs.push_back(_logs[i]);
	}
}

void Logger::GetLogsByTag(string& tag, vector<LogMessage>& logs) {
	for (size_t i = 0; i < _logs.size(); i++) {
		if (_logs[i]._tag == tag) {
			logs.push_back(_logs[i]);
		}
	}
}

void Logger::SetLogCountLimit(unsigned int limit) {
	if (limit < _maxLogCount) {
		unsigned int difference = _maxLogCount - limit;
		for (unsigned int i = 0; i < difference; i++) {
			_logs.pop_front();
		}
	}
	_maxLogCount = limit;
}

void Logger::SetLoggingDestination(LoggingDestination loggingDestination) {
	_loggingDestination = loggingDestination;
}

void Logger::SetExternalLogger(IExternalLogger* externalLogger) {
	_externalLogger = externalLogger;
}