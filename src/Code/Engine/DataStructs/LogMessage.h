#pragma once

#include <string>

using std::string;

namespace EngineECS {
	enum class LogLevel {
		Info,
		Warning,
		Error
	};

	struct LogMessage {
		LogLevel _logLevel;
		unsigned int _index;
		string _message;

		LogMessage(LogLevel logLevel, unsigned int index, string message) :
			_logLevel(logLevel),
			_index(index),
			_message(message) {
		}
	};
}