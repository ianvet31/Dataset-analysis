#include "../cs225/catch/catch.hpp"
#include "../forcegraph.h"
#include <iostream>
#include <cstdlib>

using namespace cs225;



TEST_CASE("Graph check", "[weight=5][timeout=8000]")
{

    Graph g = Graph("users_test_data.csv", "edges_test_data.csv");
    Forcegraph f = Forcegraph();
    f.setup(g, (double) (rand() % 5 + 1), (double) (rand() % 200), (double) (rand() % 100), 0.001, 1000, 1600, 900);
    std::map<int, int> graph_data = g.get_data();
    std::map<int, int> fdg_data = g.get_data();

    int graph_vertices = g.get_numVertices();
    int fdg_vertices = g.get_numVertices();

    bool isValid = true;

    for (int i = 0; i < g.get_numVertices(); i++)
    {   
        if (!(fdg_data.at(i) == graph_data.at(i))) {
            isValid = false;
        }
        if (!(graph_vertices == fdg_vertices)) {
            isValid = false;
        }
    }

    REQUIRE(isValid);
}



TEST_CASE("Positions valid check", "[weight=5][timeout=8000]")
{
    Graph g = Graph("users_test_data.csv", "edges_test_data.csv");
    Forcegraph f = Forcegraph();
    f.setup(g, (double) (rand() % 5 + 1), (double) (rand() % 200), (double) (rand() % 100), 0.001, 1000, 1600, 900);
    std::vector<std::pair<double, double>> pos = f.get_pos();
    bool isValid = true;
    for (int i = 0; i < g.get_numVertices(); i++)
    {
        if (pos[i].first > 1600 | pos[i].first < 0) {
            isValid = false;
        }
        if (pos[i].second > 900 | pos[i].second < 0) {
            isValid = false;
        }
    }
    REQUIRE(isValid);
}

TEST_CASE("Output image check", "[weight=5][timeout=8000]")
{
    Graph g = Graph("users_test_data.csv", "edges_test_data.csv");
    Forcegraph f = Forcegraph();
    f.setup(g, (double) (rand() % 5 + 1), (double) (rand() % 200), (double) (rand() % 100), 0.001, 1000, 1600, 900);
    cs225::PNG check;

    REQUIRE(check.readFromFile("FDG_out.png"));
}

