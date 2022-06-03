#pragma once
#include <SFML/Graphics.hpp>
#include "node.h"

class GameObject 
{
public:
	void Update();
	sf::RectangleShape shape;
	sf::Vector2f direction;
	sf::Vector2f position;
	Node* upAdj;
	Node* downAdj;
	Node* leftAdj;
	Node* rightAdj;
	Node* nextNode;
	Node* currentNode;
private:
	void GetNextNode();
};