#include "MessageManager.h"

using namespace EngineECS;


MessageManager::MessageManager() :
	_toBroadcast() {

}

MessageManager::~MessageManager() {
	for (IMessage* message : _toBroadcast) {
		delete message;
	}
	_toBroadcast.clear();
}

MessageManager& MessageManager::GetInstance() {
	if (!Instance) {
		Instance = new MessageManager();
	}
	return *Instance;
}

void MessageManager::ClearBroadcasts() {
	// Delete all messages in _toBroadcast
	for (IMessage* message : _toBroadcast) {
		delete message;
	}
	_toBroadcast.clear();
}

void MessageManager::AddBroadcast(IMessage* message) {
	_toBroadcast.push_back(message);
}

void MessageManager::Broadcast() {
	const vector<Entity*>* entities = EntityManager::GetInstance().GetEntities();

	for (Entity* entity : (*entities)) {
		for (IMessage* message : _toBroadcast) {
			entity->Message(message);
		}
	}
	ClearBroadcasts();
}
