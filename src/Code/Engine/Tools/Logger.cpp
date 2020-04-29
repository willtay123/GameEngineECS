#include "Logger.h"

using namespace EngineECS;

LoggingDestination Logger::_loggingDestination = LoggingDestination::Console;
unsigned int Logger::_logIndex = 0;
unsigned int Logger::_maxLogCount = MAX_LOG_COUNT;
deque<LogMessage> Logger::_logs = deque<LogMessage>();
IExternalLogger* Logger::_externalLogger = nullptr;
ofstream Logger::_logFile;
const char* Logger::LOG_FILEPATH = "Info/output.log";

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
		std::cout << LogLevelToString(message._logLevel) << ":\t" << message._message << std::endl;
		break;

	case LoggingDestination::File:
		WriteLogToFile(message);
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

void Logger::WriteLogToFile(LogMessage& message) {
	// Check if file instance is already open
	if (!_logFile.is_open()) {
		// Create the directory
		CreateDirectoryA("Info", NULL);

		// Try to open the file
		_logFile.open(Logger::LOG_FILEPATH, std::ios_base::app);

		if (_logFile.is_open()) {
			_logFile << std::endl << std::endl;
		}
		else {
			// File failed to open, default to console and make user aware
			_loggingDestination = LoggingDestination::Console;
			LogError("Unable to create log file");
		}
	}

	// Prefix the line to make reading easier
	switch (message._logLevel) {
	case LogLevel::Info:
		_logFile << "INFO:\t\t";
		break;
	case LogLevel::Warning:
		_logFile << "WARNING:\t";
		break;
	case LogLevel::Error:
		_logFile << "ERROR:\t\t";
		break;
	}

	// Write message in easily searchable format
	_logFile << "Tag: " << message._tag << " - Message: " << message._message << std::endl;
}

void Logger::Log(LogMessage& logMessage) {
	_logs.push_back(logMessage);
	if (_logs.size() > _maxLogCount) {
		_logs.pop_front();
	}
	WriteLog();
	_logIndex++;
}

string Logger::LogLevelToString(LogLevel logLevel) {
	switch (logLevel) {
	case LogLevel::Info:
		return "Info";
		break;
	case LogLevel::Warning:
		return "Warning";
		break;
	case LogLevel::Error:
		return "Error";
		break;
	default:
		return "";
		break;
	}
}

void Logger::LogInfo(const char* tag, const char* message) {
	string tagAsString = string(tag);
	string messageAsString = string(message);
	LogInfo(tagAsString, messageAsString);
}

void Logger::LogInfo(const char* message) {
	string messageAsString = string(message);
	LogInfo(messageAsString);
}

void Logger::LogInfo(const string& message) {
	string tag = string("Untagged");
	Logger::LogInfo(tag, message);
}

void Logger::LogInfo(const string& tag, const string& message) {
	LogMessage logMessage = LogMessage(LogLevel::Info, _logIndex, tag, message);
	Log(logMessage);
}

void Logger::LogWarning(const char* tag, const char* message) {
	string tagAsString = string(tag);
	string messageAsString = string(message);
	LogWarning(tagAsString, messageAsString);
}

void Logger::LogWarning(const char* message) {
	string messageAsString = string(message);
	LogWarning(messageAsString);
}

void Logger::LogWarning(const string& message) {
	string tag = string("Untagged");
	Logger::LogWarning(tag, message);
}

void Logger::LogWarning(const string& tag, const string& message) {
	LogMessage logMessage = LogMessage(LogLevel::Warning, _logIndex, tag, message);
	Log(logMessage);
}

void Logger::LogError(const char* tag, const char* message) {
	string tagAsString = string(tag);
	string messageAsString = string(message);
	LogError(tagAsString, messageAsString);
}

void Logger::LogError(const char* message) {
	string messageAsString = string(message);
	LogError(messageAsString);
}

void Logger::LogError(const string& message) {
	string tag = string("Untagged");
	Logger::LogError(tag, message);
}

void Logger::LogError(const string& tag, const string& message) {
	LogMessage logMessage = LogMessage(LogLevel::Error, _logIndex, tag, message);
	Log(logMessage);
}

void Logger::GetLogs(vector<LogMessage>& logs) {
	for (size_t i = 0; i < _logs.size(); i++) {
		logs.push_back(_logs[i]);
	}
}

void Logger::GetLogsByTag(const string& tag, vector<LogMessage>& logs) {
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