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
    void setup(Graph &graph, double springconst, double springlen, double coulombconst, double delta_time);
  
    void attractNodes(Graph &g, double sConstant, double sRestLength);
    void repelNodes(double cConstant);

    void assign_Positions();
    void updatePositions(double deltaT);


    cs225::PNG createGraphic(int w, int h);

  private:
    //private vars/functions


    
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



    void node_graphics();

    std::vector<std::pair<double, double>> node_params;  //hue [0, 360] and size of node (radius of circle)

    void applyForces(Graph &g, double springconst, double springlen, double coulombconst, double delta_time);

    bool equilibrium_check();
};
