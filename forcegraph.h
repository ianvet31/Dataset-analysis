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
  
    void attractNodes(int node1, int node2);
    void repelNodes(int node1, int node2);

    void assign_Positions();
    void setup(Graph &graph);

  private:
    //private vars/functions

    int width;
    int height;
    
    double springRestLength;
    double coulomb_constant;

    double get_xpos(int node);
    double get_ypos(int node);

    std::vector<std::pair<double, double>> pos;
    std::vector<std::pair<double, double>> forces;
    std::vector<std::tuple<double, double, double>> colors;

    int numVertices;
};
