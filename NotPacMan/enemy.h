#pragma once
#include "gameObject.h"
#include "SFML/Graphics.hpp"
#include "pathfinder.h"
#include "player.h"

class Enemy : public GameObject
{
public:
	void Init(Node grid[GRID_WIDTH][GRID_HEIGHT], Player* targetPlayer);
	void Update();
	void MoveTowardsTarget();
	bool FuzzyEquals(float a, float b, float tolerance);

	Pathfinder pathfinder;
	Player* player;
	Node* lastPlayerNode;
	Node target;
	bool targetReached = true;
};

