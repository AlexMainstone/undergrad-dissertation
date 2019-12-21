#include "World/MapGenerator.hpp"

MapGenerator::MapGenerator() 
{
    vge = VoronoiDiagramGenerator();
}

Map *MapGenerator::generate(unsigned int seed, sf::Vector2f size, unsigned int nodes) 
{
    srand(seed);

    // Generate random points
    std::vector<Point2> sites;
    sites.reserve(nodes);
    for (int i = 0; i < nodes; i++)
    {
        Point2 p;
        p.x = 1 + (rand() / (double)RAND_MAX) * (size.x - 2);
        p.y = 1 + (rand() / (double)RAND_MAX) * (size.y - 2);
        sites.push_back(p);
    }

    // Generate voronoi
    vge.compute(sites, BoundingBox(0, size.x, size.y, -1));
    Diagram *diagram = vge.relax();

    // Generate Texture
    sf::Texture map_texture = generateTexture(diagram, size);
    Map *map = new Map(map_texture);

    // Add Cities

    return map;
}

sf::Texture MapGenerator::generateTexture(Diagram *diagram, sf::Vector2f size) 
{
    sf::RenderTexture render_texture;
    render_texture.create(size.x, size.y);
    // Draw Cells
    for (Cell *c : diagram->cells)
    {
        auto pos = c->site.p;
        sf::Color col(sf::Color::White);
        col = sf::Color(rand()%255, rand()%255, rand()%255);
        sf::ConvexShape shape;
        shape.setPointCount(c->halfEdges.size() * 2);

        for (int i = 0; i < c->halfEdges.size(); i++)
        {
            shape.setPoint(i * 2, sf::Vector2f(c->halfEdges[i]->edge->vertA->x, c->halfEdges[i]->edge->vertA->y));
            shape.setPoint(i * 2 + 1, sf::Vector2f(c->halfEdges[i]->edge->vertB->x, c->halfEdges[i]->edge->vertB->y));
        }
        shape.setFillColor(col);
        render_texture.draw(shape);
    }

    render_texture.display();
    return render_texture.getTexture();
}