#include "Logger.h"

using namespace EngineECS;

Logger* Logger::_instance = 0;

Logger::Logger() :
		_loggingDestination(LoggingDestination::Console),
		_logIndex(0),
		_maxLogCount(MAX_LOG_COUNT),
		_logs() {
}

Logger::~Logger() {

}

Logger* Logger::GetInstance() {
	if (!_instance) {
		_instance = new Logger();
	}
	return _instance;
}

void Logger::WriteLog() {
	LogMessage message = _logs.back();

	switch (_loggingDestination) {
	case LoggingDestination::Console:
		std::cout << message._message << std::endl;
		break;
	case LoggingDestination::File:
		break;
	case LoggingDestination::External:
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