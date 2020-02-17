#pragma once

#include <vector>

#include "EntityManager.h"
#include "Interfaces/IMessage.h"

using std::vector;

namespace EngineECS {
	class MessageManager {
	private:
		static MessageManager* Instance;
		vector<IMessage*> _toBroadcast;

		MessageManager();

		void ClearBroadcasts();

	public:
		~MessageManager();
		static MessageManager& GetInstance();

		void AddBroadcast(IMessage* message);
		void Broadcast();
	};
}