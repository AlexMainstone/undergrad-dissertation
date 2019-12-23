#include <Scenes/Game.hpp>
#include <stdlib.h>
#include "Point2.h"

Game::Game(sf::RenderWindow &window) : window(window)
{
    // Create map
    MapGenerator *mgen = new MapGenerator();
    map = mgen->generate();
    delete mgen;
}

void Game::handleEvent(sf::Event &e)
{
    if(e.type == sf::Event::KeyPressed) {
        if(e.key.code == sf::Keyboard::R) {
            MapGenerator *mgen = new MapGenerator();
            delete map;
            map = mgen->generate();
            delete mgen;
        }
    }
}

void Game::update(float dt)
{
}

void Game::render()
{
    map->draw(window);
}