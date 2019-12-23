#include "World/MapGenerator.hpp"
#include "Markov.hpp"
#include<fstream>
#include<streambuf>

MapGenerator::MapGenerator()
{
    vge = VoronoiDiagramGenerator();
}

Map *MapGenerator::generate(unsigned int seed, sf::Vector2f size, unsigned int nodes)
{
    if(seed == 0) {
        seed = time(0);
    }
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
    std::ifstream t("../res/names.txt");
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());

    Markov markov(2, str);

    for(int i = 0; i < rand() % 10 + 10; i++) {
        auto randmap = diagram->cells[rand() % diagram->cells.size()];
        while(mapprop[randmap]->tile == 0) {
            randmap = diagram->cells[rand() % diagram->cells.size()];
        }
        map->addCity(City(sf::Vector2f(randmap->site.p.x, randmap->site.p.y), markov.generate()));
    }

    for(auto it = mapprop.begin(); it != mapprop.end(); it++) {
        delete it->second;
    }
    mapprop.clear();
    delete (diagram);


    return map;
}

std::map<Cell*, MapCell*> MapGenerator::initCellProperties(Diagram *diagram)
{
    std::map<Cell*, MapCell*> cells;

    siv::PerlinNoise noise(time(0));
    for (auto c : diagram->cells)
    {
        float dist = std::sqrt(std::pow(c->site.p.x - (1280/2), 2) + std::pow(c->site.p.y - (720/2),2));
        // if(dist < 200) {
        //     cells[c] = new MapCell(1, 0);
        // } else {
        //     cells[c] = new MapCell(0, 0);
        // }
        
        float n = noise.noise(c->site.p.x/100, c->site.p.y/100) - (dist/300);
        if(n > -0.9) {
            cells[c] = new MapCell(n, 1);
        } else {
            cells[c] = new MapCell(n, 0);
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
        if(mapprop[c]->altitude <= -0.9) {
            col = sf::Color(200, 200, 255);
        } else if(mapprop[c]->altitude > 0.15) {
            col = sf::Color(255, 255, 255);
        } else if(mapprop[c]->altitude > -0.1) {
            col = sf::Color(150, 150, 150);
        } else {
            col = sf::Color(200, 255, 200);
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
            if(mapprop[e->edge->lSite->cell]->tile != mapprop[e->edge->rSite->cell]->tile) {
                // define points
                float x1 = e->edge->vertA->x;
                float y1 = e->edge->vertA->y;
                float x2 = e->edge->vertB->x;
                float y2 = e->edge->vertB->y;

                // Add line
                templines.push_back(sf::Vector2f(x1, y1));
                templines.push_back(sf::Vector2f(x2, y2));

                // Parallel line
                float L = std::sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
                float offset = 2;

                float x1p = x1 + offset * (y2-y1) / L;
                float y1p = y1 + offset * (x1-x2) / L;
                float x2p = x2 + offset * (y2-y1) / L;
                float y2p = y2 + offset * (x1-x2) / L;
                // Add line
                templines.push_back(sf::Vector2f(x1p, y1p));
                templines.push_back(sf::Vector2f(x2p, y2p));
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