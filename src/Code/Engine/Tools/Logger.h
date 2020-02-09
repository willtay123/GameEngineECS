#pragma once


namespace EngineECS {
	class Logger {
	private:
		static Logger* _instance;
		Logger();
		~Logger();

	public:
		static Logger* GetInstance();
	};
}

