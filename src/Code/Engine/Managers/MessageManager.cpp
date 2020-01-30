#include "MessageManager.h"


namespace EngineECS {
	vector<IMessage*>* MessageManager::_toBroadcast;

	void MessageManager::ClearBroadcasts() {
		// Delete all messages in _toBroadcast
		for (IMessage* message : (*_toBroadcast)) {
			delete message;
		}

		// Clear _toBroadcast
		_toBroadcast->clear();
	}

	void MessageManager::Initialise() {
		_toBroadcast = new vector<IMessage*>();
	}

	void MessageManager::AddBroadcast(IMessage* message) {
		_toBroadcast->push_back(message);
	}

	void MessageManager::Broadcast() {
		const vector<Entity*>* entities = EntityManager::GetEntities();

		for (Entity* entity : (*entities)) {
			for (IMessage* message : (*_toBroadcast)) {
				entity->Message(message);
			}
		}

		ClearBroadcasts();
	}

	void MessageManager::End() {

	}
}