#pragma once

#include <SFML/Graphics.hpp>
#include "VoronoiDiagramGenerator.h"
#include "PerlinNoise.hpp"
#include "World/Map.hpp"

class MapGenerator
{
public:
    MapGenerator();
    Map *generate(unsigned int seed = 0, sf::Vector2f size = sf::Vector2f(1281, 721), unsigned int nodes = 10000);
private:
    sf::Texture generateTexture(Diagram *diagram, sf::Vector2f size);

    VoronoiDiagramGenerator vge;
};