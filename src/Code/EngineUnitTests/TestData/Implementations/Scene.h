#pragma once
#include "Interfaces/IScene.h"

using namespace EngineECS;

class Scene : public IScene {
private:

public:
	Scene(const string& name) {
		_name = name;
	}

	virtual void Initialise() override;
	virtual void Render() override;
	virtual void Update(double dt) override;
	virtual void Close() override;
};