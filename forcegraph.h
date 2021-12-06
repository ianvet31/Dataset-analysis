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

  
    void setup(Graph & graph, double springconst, double springlen, double coulombconst, double delta_time);
  
    void attractNodes(double sConstant, double sRestLength);
    void repelNodes(double cConstant);

    void assign_Positions();
    void Forcegraph::updatePositions(double deltaT);


    cs225::PNG Forcegraph::createGraphic(int w, int h);

  private:
    //private vars/functions

    Graph g;

    cs225::PNG output_FDG;

    int width;
    int height;

    // id, views (important/relevant data)
        std::map<int, int> data;


    int numVertices;
    
    std::vector<std::map<int, int>> vertices;     //nodes w data, but will want more data
    std::vector<std::pair<int, int>> edges;    //prob bad implementation, but vector of edges between int user ids


      
    std::vector<std::pair<double, double>> pos;
    std::vector<std::pair<double, double>> forces;
    std::vector<std::tuple<double, double, double>> colors;



    void Forcegraph::node_graphics();

    std::vector<std::pair<double, double>> node_params;  //hue [0, 360] and size of node (radius of circle)

    void Forcegraph::applyForces(double springconst, double springlen, double coulombconst, double delta_time);

    bool Forcegraph::equilibrium_check();
};
