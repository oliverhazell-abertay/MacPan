#pragma once
#include <SFML/Graphics.hpp>
#include "node.h"
#include "player.h"
#include "enemy.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#define GRID_WIDTH 19
#define GRID_HEIGHT 11

class Application
{
public:
	void Init(sf::RenderWindow* window);
	void CleanUp();
	int Update(float dt);
	void Input(float dt);
	void Render();
	void InitGrid();
	// Grid loading
	void FileToGrid(std::string filename);
	// Fuzzy equals for player turning
	bool FuzzyEquals(float a, float b, float tolerance);
	// Collision detection
	bool AABBCollision(sf::RectangleShape a, sf::RectangleShape b);
	sf::Vector2i FindCurrentNode(GameObject gameObject);
	// Calculate enemy current node and update. Needed for multithreading
	void UpdateEnemy(Enemy* enemy, float dt);

	// Screen grid variables
	Node grid[GRID_WIDTH][GRID_HEIGHT];
	const float shapeWidth = WINDOW_WIDTH / GRID_WIDTH;
	const float shapeHeight = WINDOW_HEIGHT / GRID_HEIGHT;
	sf::RenderWindow* window;
	sf::Font myFont;

private:
	// Player object
	Player* player;
	// Enemies
	Enemy* blinky;
	Enemy* inky;
	Enemy* pinky;

	// Fuzzy equals for turning variable
	float movementTolerance = 10.0f;



};