#include "Application.h"
#include <thread>
#include <chrono>

void Application::Init(sf::RenderWindow* wind)
{
    window = wind;
    // Init grid
    InitGrid();
    // Init player
    player.playerShape.setPosition(0.0f, 0.0f);
    player.playerShape.setSize(sf::Vector2f(shapeWidth, shapeHeight));
    player.playerShape.setFillColor(sf::Color::Green);
    player.playerShape.setOutlineColor(sf::Color::Black);
    player.playerShape.setOutlineThickness(5.0f);
    player.direction = sf::Vector2f(1.0f, 0.0f);
}

void Application::CleanUp()
{
    delete window;
    window = NULL;
}

int Application::Update()
{

    while (window->isOpen())
    {
        window->setKeyRepeatEnabled(false);
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            // ESC - Close window
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window->close();
            // WASD movement
            // Left arrow
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                player.direction = sf::Vector2f(-1.0f, 0.0f);
            }
            // Right arrow
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                player.direction = sf::Vector2f(1.0f, 0.0f);
            }
            // Up arrow
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                player.direction = sf::Vector2f(0.0f, -1.0f);
            }
            // Down arrow
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                player.direction = sf::Vector2f(0.0f, 1.0f);
            }
        }
        // Update player position
        playerTimer++;
        if (playerTimer > playerTimerMax)
        {
            sf::Vector2f tempPos;
            tempPos.x = player.playerShape.getPosition().x + (shapeWidth * player.direction.x);
            tempPos.y = player.playerShape.getPosition().y + (shapeHeight * player.direction.y);
            player.playerShape.setPosition(tempPos);
            playerTimer = 0.0f;
        }
        // Render
        Render();
    }

    return 0;
}

void Application::Render()
{
    window->clear();
    // Draw grid
    for (int i = 0; i < gridWidth; i++)
    {
        for (int j = 0; j < gridHeight; j++)
        {
            window->draw(grid[i][j]);
        }
    }
    window->draw(player.playerShape);
    window->display();
}

void Application::InitGrid()
{
    for (int i = 0; i < gridWidth; i++)
    {
        for (int j = 0; j < gridHeight; j++)
        {
            // Variables
            grid[i][j].setSize(sf::Vector2f(shapeWidth, shapeHeight));
            grid[i][j].setPosition(sf::Vector2f(i * shapeWidth, j * shapeHeight));
            grid[i][j].setFillColor(sf::Color::White);
            grid[i][j].setOutlineColor(sf::Color::Black);
            grid[i][j].setOutlineThickness(5.0f);
        }
    }
}