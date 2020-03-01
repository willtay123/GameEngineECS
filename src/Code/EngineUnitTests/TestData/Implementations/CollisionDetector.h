#pragma once
#include "Interfaces/ICollisionDetector.h"
#include "CleverPointers.h"

using namespace EngineECS;

class CollisionDetector : public ICollisionDetector {
private:

public:
	void DetectCollisions(const shared_ptr<const EntityList> entityList, vector<ICollisionManifold*>& collisions) override;

};

