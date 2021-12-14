/**
 * @file forcegraph.h
 * Definition of a class for the force-directed graph algorithm
 */

#pragma once
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>
#include <vector>
#include <map>
#include "graph.h"



class Forcegraph {
  public:

    Forcegraph();
    void setup(Graph graph, double springconst, double springlen, double coulombconst, double delta_time, int max_i_, unsigned wid, unsigned hei);
  
    void attractNodes(Graph g, double sConstant, double sRestLength);
    void repelNodes(double cConstant);

    void assign_Positions();
    void updatePositions(double deltaT);


    void createGraphic(Graph graph);

    std::map<int, int> get_data();
    std::vector<std::pair<double, double>> get_pos();

  private:
    
    cs225::PNG output_FDG;

    unsigned width;
    unsigned height;

    // id, views (important/relevant data)
    std::map<int, int> data;


    int numVertices;
    
    std::vector<std::map<int, int>> vertices;
    std::vector<std::pair<int, int>> edges;
    std::vector<std::pair<double, double>> pos; 
    std::vector<std::pair<double, double>> forces;



    void node_graphics();

    std::vector<std::pair<double, double>> node_params;  //hue [0, 360] and size of node (radius of circle)

    void applyForces(Graph g, double springconst, double springlen, double coulombconst, double delta_time, int max_i_);

    bool equilibrium_check();

};
