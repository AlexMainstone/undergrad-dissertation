#include <Scenes/Game.hpp>
#include <stdlib.h>
#include "Point2.h"

Game::Game(sf::RenderWindow &window) : window(window)
{
    // Create map

    MapGenerator *mgen = new MapGenerator();
    map = mgen->generate();
    zoom = 1;
    delete mgen;
}

void Game::handleEvent(sf::Event &e)
{
    if (e.type == sf::Event::KeyPressed)
    {
        if (e.key.code == sf::Keyboard::R)
        {
            MapGenerator *mgen = new MapGenerator();
            delete map;
            map = mgen->generate();
            delete mgen;
        }
    } else if(e.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i pixel(e.mouseButton.x, e.mouseButton.y);
        const sf::Vector2f before(window.mapPixelToCoords(pixel));
        sf::View view(window.getView());;
        view.zoom(zoom-=0.1);
        window.setView(view);
        const sf::Vector2f after(window.mapPixelToCoords(pixel));
        const sf::Vector2f finalCoord(before - after);
        view.move(finalCoord);
        window.setView(view);
    }
    map->handleEvent(e);
}

void Game::update(float dt)
{
}

void Game::render()
{
    map->draw(window);
}