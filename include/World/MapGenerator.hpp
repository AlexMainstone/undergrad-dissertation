#pragma once

#include <SFML/Graphics.hpp>
#include "VoronoiDiagramGenerator.h"
#include "PerlinNoise.hpp"
#include "World/Map.hpp"

struct MapCell {
    unsigned int altitude;
    unsigned int tile;
    MapCell(unsigned int altitude) : altitude(altitude) {};
};

class MapGenerator
{
public:
    MapGenerator();
    Map *generate(unsigned int seed = 0, sf::Vector2f size = sf::Vector2f(1281, 721), unsigned int nodes = 10000);

private:
    std::map<Cell*, MapCell*> initCellProperties(Diagram *diagram);
     
    sf::Texture generateTexture(Diagram *diagram, std::map<Cell*, MapCell*> mapprop, sf::Vector2f size);
    sf::VertexArray generateConvexShapes(std::map<Cell*, MapCell*> mapprop, Diagram *diagram);


    VoronoiDiagramGenerator vge;
};