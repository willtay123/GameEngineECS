#pragma once

#include <string>

using std::string;

namespace EngineECS {
	class IMessage {
	private:
	
	public:
		virtual ~IMessage() {}
		virtual const string& GetSenderID() const = 0;
	};
}