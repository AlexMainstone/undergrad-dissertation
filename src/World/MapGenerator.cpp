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

    // Initialize Map properties
    auto mapprop = initCellProperties(diagram);

    // Erode

    // Generate Texture
    sf::Texture map_texture = generateTexture(diagram, mapprop, size);
    Map *map = new Map(map_texture, generateConvexShapes(mapprop, diagram));

    // Add Cities

    return map;
}

std::map<Cell*, MapCell*> MapGenerator::initCellProperties(Diagram *diagram)
{
    std::map<Cell*, MapCell*> cells;

    for (auto c : diagram->cells)
    {
        if(c->site.p.x < 700) {
            cells[c] = new MapCell(1);
        } else {
            cells[c] = new MapCell(0);
        }
    }

    return cells;
}

sf::Texture MapGenerator::generateTexture(Diagram *diagram, std::map<Cell*, MapCell*> mapprop, sf::Vector2f size)
{
    sf::RenderTexture render_texture;
    render_texture.create(size.x, size.y);
    // Draw Cells
    for (Cell *c : diagram->cells)
    {
        auto pos = c->site.p;
        sf::Color col(sf::Color::White);
        if(mapprop[c]->altitude == 0) {
            col = sf::Color::Black;
        } else {
            col = sf::Color::White;
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
    return render_texture.getTexture();
}

sf::VertexArray MapGenerator::generateConvexShapes(std::map<Cell*, MapCell*> mapprop, Diagram *diagram)
{
    std::vector<sf::Vector2f> templines;

    for (auto c : diagram->cells)
    {
        for(auto e : c->halfEdges) {
            if(e->edge->lSite == nullptr || e->edge->rSite == nullptr) {
                continue;
            }
            if(mapprop[e->edge->lSite->cell]->altitude != mapprop[e->edge->rSite->cell]->altitude) {
                // Add line
                templines.push_back(sf::Vector2f(e->edge->vertA->x, e->edge->vertA->y));
                templines.push_back(sf::Vector2f(e->edge->vertB->x, e->edge->vertB->y));
            }
        }
    }

    sf::VertexArray lines(sf::Lines, templines.size());
    for(int i = 0; i < templines.size(); i++) {
        lines[i].position = templines[i];
        lines[i].color = sf::Color::Black;
    }
    return lines;
}
