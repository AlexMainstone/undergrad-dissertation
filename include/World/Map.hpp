#pragma once

#include <SFML/Graphics.hpp>
#include "VoronoiDiagramGenerator.h"
#include "PerlinNoise.hpp"

class Map
{
public:
    void generate(unsigned int seed = 0, sf::Vector2f size = sf::Vector2f(1281, 721), unsigned int nodes = 10000);

    void updateMap();

    void draw(sf::RenderWindow &window);

private:
    sf::RenderTexture render_texture;
    sf::Sprite sprite;

    sf::Vector2f size;

    Diagram *diagram;
    VoronoiDiagramGenerator vge;
    
    const siv::PerlinNoise *perlin;
};