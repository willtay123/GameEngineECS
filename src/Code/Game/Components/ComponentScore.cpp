#include "ComponentScore.h"



ComponentScore::ComponentScore() {
	_componentType = ComponentManager::GetInstance().GenerateIDByString("score");
	_score = 0;
}

ComponentScore::ComponentScore(int score) {
	_componentType = ComponentManager::GetInstance().GenerateIDByString("score");
	_score = score;
}

ComponentScore::ComponentScore(const ComponentScore& rhs) {
	_score = rhs._score;
}

ComponentScore::~ComponentScore() {

}

ComponentScore& ComponentScore::operator=(const ComponentScore& rhs) {
	if (this != &rhs) {
		_score = rhs._score;
	}
	return *this;
}

IComponent* ComponentScore::Clone() {
	return new ComponentScore();
}

int ComponentScore::ComponentType() const {
	return _componentType;
}

void ComponentScore::Message(IMessage* message) {

}

void ComponentScore::IncreaseScore(int value) {
	_score += value;
}

void ComponentScore::ResetScore() {
	_score = 0;
}

int ComponentScore::GetScore() {
	return _score;
}