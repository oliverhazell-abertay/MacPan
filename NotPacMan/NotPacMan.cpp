#include <iostream>
#include <SFML/Graphics.hpp>
#include "application.h"

float deltaTime = 0.0f;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "NotPacMan");
    window.setFramerateLimit(60);

    Application application;
    application.Init(&window);

    sf::Clock deltaClock;

    while (window.isOpen())
    {
        sf::Time dt = deltaClock.restart();
        application.Update(dt.asSeconds());
    }

    return 0;
}