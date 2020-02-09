#include "Logger.h"

using namespace EngineECS;

Logger* Logger::_instance = 0;

Logger::Logger() :
		_loggingDestination(LoggingDestination::Console),
		_logIndex(0),
		_maxLogCount(50),
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
	LogMessage message = _logs.front();

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

void Logger::LogInfo(string& message) {
	LogMessage* logMessage = new LogMessage(LogLevel::Info, _logIndex, message);
	Log(*logMessage);
}

void Logger::LogWarning(string& message) {
	LogMessage* logMessage = new LogMessage(LogLevel::Warning, _logIndex, message);
	Log(*logMessage);
}

void Logger::LogError(string& message) {
	LogMessage* logMessage = new LogMessage(LogLevel::Error, _logIndex, message);
	Log(*logMessage);
}