#pragma once
#include "gameObject.h"

class Player : public GameObject
{
public:
	Player(sf::Vector2f startPos, sf::Vector2f size, float startSpeed);
	void Update(float dt);
	bool powered = false;
private:
	void EatPellets();
	// Power pellet variables
	float powerTimer = 0.0f;
	float powerDuration = 5.0f;
};

