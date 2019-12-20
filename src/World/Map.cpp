#include <World/Map.hpp>


void Map::generate(unsigned int seed, sf::Vector2f size, unsigned int nodes) 
{
    srand(seed);

    perlin = new siv::PerlinNoise(seed);

    this->size = size;

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
    vge = VoronoiDiagramGenerator();
    vge.compute(sites, BoundingBox(0, size.x, size.y, -1));
    diagram = vge.relax();

    // Draw map to texture
    updateMap();
}

void Map::updateMap()
{
    render_texture.create(size.x, size.y);
    // Draw Cells
    for (Cell *c : diagram->cells)
    {
        auto pos = c->site.p;
        sf::Color col(sf::Color::White);
        if(pos.y > pos.x*0.9- 500) {
            col = sf::Color(230, 230, 230);
        }
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
    sprite.setTexture(render_texture.getTexture());
}

void Map::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}