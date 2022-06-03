#pragma once
#include "gameObject.h"
#include "SFML/Graphics.hpp"
#include "node.h"

class Enemy : public GameObject
{
public:
	sf::RectangleShape enemyShape;
	sf::Vector2f direction;
	sf::Vector2f position;
};

