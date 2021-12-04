/**
 * @file forcegraph.h
 * Definition of a class for the force-directed graph algorithm
 */

#pragma once
#include <string>
#include <vector>
#include <map>
#include "Graph.h"

class Forcegraph {
  public:

    void setup(Graph &graph);
  
    void attractNodes(int node1, int node2, double sConstant, double sRestLength);
    void repelNodes(int node1, int node2, double cConstant);

    void assign_Positions();
    void Forcegraph::updatePositions(double deltaT);

    bool Forcegraph::equilibrium_check();

    cs225::PNG Forcegraph::createGraphic(int w, int h);

  private:
    //private vars/functions

    Graph g;

    cs225::PNG output_FDG;

    // id, views (important/relevant data)
        std::map<int, int> data;

    std::vector<std::map<int, int>> vertices;     //nodes w data, but will want more data
    std::vector<std::pair<int, int>> edges;    //prob bad implementation, but vector of edges between int user ids
  

    int width;
    int height;

    double get_xpos(int node);
    double get_ypos(int node);

      
    std::vector<std::pair<double, double>> pos;
    std::vector<std::pair<double, double>> forces;
    std::vector<std::tuple<double, double, double>> colors;

    int numVertices;
};
