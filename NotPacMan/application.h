#pragma once
#include <SFML/Graphics.hpp>
#include "node.h"
#include "player.h"
#include "pathfinder.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#define GRID_WIDTH 19
#define GRID_HEIGHT 11

class Application
{
public:
	void Init(sf::RenderWindow*);
	void CleanUp();
	int Update();
	void Render();
	void InitGrid();
	void FileToGrid(std::string);
	bool FuzzyEquals(float a, float b, float tolerance);

	Node grid[GRID_WIDTH][GRID_HEIGHT];
	const float shapeWidth = WINDOW_WIDTH / GRID_WIDTH;
	const float shapeHeight = WINDOW_HEIGHT / GRID_HEIGHT;
	sf::RenderWindow* window;
	sf::Font myFont;

	// Player values -- TO BE MOVED TO PLAYER CLASS
	Player player;
	float playerTimer;
	float playerTimerMax = 50;
	float playerSpeed = 1.5f;
	float movementTolerance = 10.0f;

	Pathfinder pathfinder;
};