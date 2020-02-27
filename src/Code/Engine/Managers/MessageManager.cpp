#include "MessageManager.h"

using namespace EngineECS;


MessageManager* MessageManager::Instance = nullptr;

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
	//std::shared_ptr<EntityList> entities = EntityManager::GetInstance().GetEntities().lock();
	//if (entities != nullptr) {
	//	for (int i = 0; i < entities->size(); i++) {
	//		std::shared_ptr<Entity> entity = (*entities)[i].lock();
	//		for (IMessage* message : _toBroadcast) {
	//			entity->Message(message);
	//		}
	//	}
	//	ClearBroadcasts();
	//}
}
