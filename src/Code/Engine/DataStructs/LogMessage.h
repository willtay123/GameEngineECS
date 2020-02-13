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
		string _tag;
		string _message;

		LogMessage(LogLevel logLevel, unsigned int index, string message) :
			_logLevel(logLevel),
			_index(index),
			_tag(),
			_message(message) {
		}

		LogMessage(LogLevel logLevel, unsigned int index, string tag, string message) :
			_logLevel(logLevel),
			_index(index),
			_tag(tag),
			_message(message) {
		}
	};
}