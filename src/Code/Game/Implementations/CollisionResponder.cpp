#pragma once
#include "CollisionResponder.h"



CollisionResponder::CollisionResponder() {

}

CollisionResponder::~CollisionResponder() {

}

void CollisionResponder::HandleCollisions(const vector<ICollisionManifold*>& manifoldList) {
	for (ICollisionManifold* iManifold : manifoldList) {
		//handle collisions

		CollisionManifold* manifold = (CollisionManifold*)iManifold;

		Entity* entity1 = manifold->GetEntity1();
		Entity* entity2 = manifold->GetEntity2();


		std::size_t found1 = entity1->GetID().find("item_");
		std::size_t found2 = entity2->GetID().find("item_");

		// Ensure not both items
		if (found1 == 0 && found2 == 0) {
			// Dont care about this collision
			continue;
		}

		// Player Item
		if (entity1->GetID() == "player" && found2 == 0) {
			HandlePlayerItem(entity1, entity2);
		}

		// Item Player
		if (found1 == 0 && entity2->GetID() == "player") {
			HandlePlayerItem(entity2, entity1);
		}
	}
}

void CollisionResponder::HandlePlayerItem(Entity* player, Entity* item) {
	Logger::LogInfo("Player-Item collision");

	// Delete Item
	string itemName = item->GetID();
	EntityManager::GetInstance().RemoveEntity("game", itemName);

	// Add score to player
	int scoreID = ComponentManager::GetInstance().GetIDForType(typeid(ComponentScore));
	ComponentScore* scoreComp = (ComponentScore*)player->GetComponentEditable(scoreID);
	scoreComp->IncreaseScore(1);
}