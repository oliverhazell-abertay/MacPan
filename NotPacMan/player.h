#pragma once
#include "gameObject.h"

class Player : public GameObject
{
public:
	void Update(float dt);
	bool powered = false;
private:
	void EatPellets();
	float powerTimer = 0.0f;
	float powerDuration = 5.0f;
};

