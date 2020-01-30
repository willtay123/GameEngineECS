#pragma once

#include <string>

using std::string;

namespace EngineECS {
	class IMessage {
	private:
		virtual const string* GetSenderID() const = 0;
	};
}