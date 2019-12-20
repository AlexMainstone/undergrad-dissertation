#include <Scenes/Game.hpp>
#include <stdlib.h>
#include "Point2.h"

Game::Game(sf::RenderWindow &window) : window(window)
{
    // Create map
    map = new Map();
    map->generate(time(0));
}

void Game::handleEvent(sf::Event &e)
{
}

void Game::update(float dt)
{
}

void Game::render()
{
    map->draw(window);
}