#include "Logger.h"

using namespace EngineECS;

LoggingDestination Logger::_loggingDestination = LoggingDestination::Console;
unsigned int Logger::_logIndex = 0;
unsigned int Logger::_maxLogCount = MAX_LOG_COUNT;
queue<LogMessage> Logger::_logs = queue<LogMessage>();
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
	_logs.push(logMessage);
	if (_logs.size() > _maxLogCount) {
		_logs.pop();
	}
	WriteLog();
	_logIndex++;
}

void Logger::LogInfo(const char* message) {
	string messageAsString = string(message);
	LogInfo(messageAsString);
}

void Logger::LogInfo(string& message) {
	LogMessage* logMessage = new LogMessage(LogLevel::Info, _logIndex, message);
	Log(*logMessage);
}

void Logger::LogWarning(const char* message) {
	string messageAsString = string(message);
	LogWarning(messageAsString);
}

void Logger::LogWarning(string& message) {
	LogMessage* logMessage = new LogMessage(LogLevel::Warning, _logIndex, message);
	Log(*logMessage);
}

void Logger::LogError(const char* message) {
	string messageAsString = string(message);
	LogError(messageAsString);
}

void Logger::LogError(string& message) {
	LogMessage* logMessage = new LogMessage(LogLevel::Error, _logIndex, message);
	Log(*logMessage);
}

void Logger::SetLoggingDestination(LoggingDestination loggingDestination) {
	_loggingDestination = loggingDestination;
}

void Logger::SetExternalLogger(IExternalLogger* externalLogger) {
	_externalLogger = externalLogger;
}