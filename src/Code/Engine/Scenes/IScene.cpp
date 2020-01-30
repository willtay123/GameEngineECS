#include "Interfaces/IScene.h"

namespace EngineECS {
	IScene::IScene() : _name("default") {

	}

	const string* IScene::GetName() const {
		return &_name;
	}
}