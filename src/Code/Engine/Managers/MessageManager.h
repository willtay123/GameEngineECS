#pragma once

#include <vector>

#include "EntityManager.h"
#include "Interfaces/IMessage.h"

using std::vector;


class MessageManager {
private:
	static vector<IMessage*>* _toBroadcast;

	static void ClearBroadcasts();

public:
	static void Initialise();

	static void AddBroadcast(IMessage* message);
	static void Broadcast();

	static void End();
};