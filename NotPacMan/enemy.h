#pragma once
#include "gameObject.h"
#include "SFML/Graphics.hpp"
#include "pathfinder.h"
#include "player.h"

class Enemy : public GameObject
{
public:
	void Init(Node grid[GRID_WIDTH][GRID_HEIGHT], Player* targetPlayer, Node* home);
	void Update(float dt);
	void MoveTowardsTarget();
	bool FuzzyEquals(float a, float b, float tolerance);
	void Flash(float dt);

	Pathfinder pathfinder;
	Player* player;
	Node* lastPlayerNode;
	Node target;
	Node* homeNode;
	bool targetReached = true;
	bool flashing = false;
	float flashTimer = 0.0f;
	float flashFreq = 0.1f;
	sf::Color currentColour;
	sf::Color mainColour;
	sf::Color flashColourLight;
	sf::Color flashColourDark;
};

