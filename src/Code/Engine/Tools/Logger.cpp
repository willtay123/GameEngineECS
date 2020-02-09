#include "Logger.h"

using namespace EngineECS;

Logger* Logger::_instance = 0;

Logger::Logger() :
	_loggingDestination(LogConsole) {

}

Logger::~Logger() {

}

Logger* Logger::GetInstance() {
	if (!_instance) {
		_instance = new Logger();
	}
	return _instance;
}