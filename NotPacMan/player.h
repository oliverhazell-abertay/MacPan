#pragma once
#include "gameObject.h"

class Player : public GameObject
{
public:
	void Update();
private:
	void EatPellets();
};

