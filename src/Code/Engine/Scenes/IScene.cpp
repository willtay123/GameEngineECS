#include "Interfaces/IScene.h"

IScene::IScene() : _name("default") {

}

const string* IScene::GetName() const {
	return &_name;
}