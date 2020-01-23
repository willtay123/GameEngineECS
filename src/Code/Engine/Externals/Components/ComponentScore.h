#pragma once
#include "Interfaces/IComponent.h"



class ComponentScore : public IComponent {
private:
	int _score;

public:
	ComponentScore();
	ComponentScore(int score);
	ComponentScore(const ComponentScore& rhs);
	~ComponentScore();
	ComponentScore& operator=(const ComponentScore& rhs);

	IComponent* Clone();

	int ComponentType() const;
	void Message(IMessage* message);

	void IncreaseScore(int value);
	void ResetScore();
	int GetScore();
};