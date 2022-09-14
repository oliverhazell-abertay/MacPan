#pragma once
#include "gameObject.h"
#include "SFML/Graphics.hpp"
#include "pathfinder.h"
#include "player.h"

class Enemy : public GameObject
{
public:
	Enemy(Node grid[GRID_WIDTH][GRID_HEIGHT], Player* targetPlayer, Node* home, sf::Vector2f startPos, sf::Vector2f size, sf::Color color, float startSpeed);
	void Update(float dt);
	void MoveTowardsTarget();
	bool FuzzyEquals(float a, float b, float tolerance);
	void Flash(float dt);

private:
	// Pathfinding
	Pathfinder pathfinder;
	Player* player;
	Node* lastPlayerNode; // Recalculate path when lastPlayerNode != player's current node
	Node target; // Either player or home depending on player being empowered
	Node* homeNode; // Corner to run to when player is empowered
	bool targetReached = true;
	// Flashing variables
	bool flashing = false;
	float flashTimer = 0.0f;
	float flashFreq = 0.1f;
	// Colours
	sf::Color currentColour;
	sf::Color mainColour;
	sf::Color flashColourLight;
	sf::Color flashColourDark;
};

