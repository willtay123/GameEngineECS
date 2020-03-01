#pragma once

#include "Interfaces/ICollisionResponder.h"

using namespace EngineECS;

class CollisionResponder : public ICollisionResponder {
private:

public:
	void HandleCollisions(const vector<ICollisionManifold*>& manifoldList) override;
};