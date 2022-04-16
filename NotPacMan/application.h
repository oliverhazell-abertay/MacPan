#pragma once
#include <SFML/Graphics.hpp>
#include "player.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

class Application
{
public:
	void Init(sf::RenderWindow*);
	void CleanUp();
	int Update();
	void Render();
	void InitGrid();

	const static int gridWidth = 10;
	const static int gridHeight = 6;
	sf::RectangleShape grid[gridWidth][gridHeight];
	const float shapeWidth = WINDOW_WIDTH / gridWidth;
	const float shapeHeight = WINDOW_HEIGHT / gridHeight;
	sf::RenderWindow* window;
	sf::Font myFont;

	Player player;
	float playerTimer;
	float playerTimerMax = 10;
};