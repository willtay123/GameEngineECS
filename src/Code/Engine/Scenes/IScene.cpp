#include "Interfaces/IScene.h"

using namespace EngineECS;

IScene::IScene() : _name("default") {

}

const string* IScene::GetName() const {
	return &_name;
}