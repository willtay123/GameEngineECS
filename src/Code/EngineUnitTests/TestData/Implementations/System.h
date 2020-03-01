#pragma once

#include <Interfaces/ISystem.h>

using namespace EngineECS;

class System : public ISystem {
private:

public:

	// Inherited via ISystem
	const string* GetName() override;
	void GiveEntities(vector<Entity*>* entityList) override;
	void OnAction(double deltaTime) override;
};