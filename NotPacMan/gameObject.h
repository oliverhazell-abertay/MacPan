#pragma once
#include <SFML/Graphics.hpp>
#include "node.h"

class GameObject 
{
public:
	void Update(float dt);
	sf::RectangleShape shape;
	sf::Vector2f direction;
	sf::Vector2f position;
	// Neighbours
	Node* upAdj;
	Node* downAdj;
	Node* leftAdj;
	Node* rightAdj;
	Node* nextNode;
	Node* currentNode;
	// Getters + Setters
	inline void SetSpeed(float nextSpeed) { speed = nextSpeed; }
	inline float GetSpeed() { return speed; }

private:
	void GetNextNode();
	void CollisionDetection();

	float speed = 1.0f;
};