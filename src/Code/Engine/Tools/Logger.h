#pragma once


namespace EngineECS {
	enum LoggingDestination {
		LogConsole,
		LogFile,
		LogExternal // If mode changes to external and link is broken, default to console
	};

	class Logger {
	private:
		static Logger* _instance;
		Logger();
		~Logger();

		LoggingDestination _loggingDestination;

	public:
		static Logger* GetInstance();
	};
}

