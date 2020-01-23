#pragma once

#include <string>

using std::string;

class IMessage {

private:
	virtual const string* GetSenderID() const = 0;
};