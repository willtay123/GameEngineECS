#pragma once

#include <string>

using std::string;

namespace EngineECS {
	class IMessage {
	private:
	
	public:
		virtual const string& GetSenderID() const = 0;
		virtual ~IMessage() = 0;
	};
}