#include "DefaultScene.h"

using namespace EngineECS;

DefaultScene::DefaultScene() {
	_name = "Default Scene";
	Logger::LogError("ERROR: No scene has been set!");
}

DefaultScene::~DefaultScene() {

}

void DefaultScene::Initialise() {

}

void DefaultScene::Update(double dt) {
}

void DefaultScene::Render() {

}

void DefaultScene::Close() {

}