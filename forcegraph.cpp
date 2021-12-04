/**
 * @file forcegraph.cpp
 * Implementation of force-directed graph algorithm
 */

#include "forcegraph.h"
#include "graph.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <vector>
#include <math.h>
#include <cs225/PNG.h>
#include <cs225/HSLAPixel.h>

using namespace cs225;

//todo - more setup, fix force functions, add equilibrium check, add graphics


// update positions over some delta_time for iterations, equil check each time




void Forcegraph::setup(Graph & graph) {   // will want to assign nodes color, size, etc.

    g = graph;
    numVertices = graph.get_numVertices();
    data = graph.get_data();

    for (int i = 0; i < numVertices + 1; i++) {
      for (int j = 0; j < numVertices + 1; j++) {
        if (graph.amatrix[i][j] == 1) {
          edges.push_back(std::make_pair(i, j));
        }
      }
    }





    return;
}


bool Forcegraph::equilibrium_check() {        // confirms that x and y components of force are zero for each node

  for (int i = 0; i < numVertices + 1; i++) {
    if (forces[i].first != 0 || forces[i].second != 0) {
      return false;
    }
  }
  return true;

}


// Assigns completely random positions for nodes, maybe change later


void Forcegraph::assign_Positions() {

    pos.resize(numVertices, {0, 0});          //init position and forces for nodes
    forces.resize(numVertices, {0, 0});

    for (int i = 0; i < numVertices + 1; i++) {
      pos.push_back(std::make_pair(std::rand() % width, std::rand() % height)); 
    }

}


// maybe change force functions to loop through all nodes, not two at a time..
 
void Forcegraph::attractNodes(int node1, int node2, double springConstant, double springRestLength) {
  //use Hooke's Law

  if (!g.is_connected(node1, node2)) {
    return;
  }
  

  double deltaX = pos[node1].first - pos[node2].first;
  double deltaY = pos[node1].second - pos[node2].second;

  double distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

  if (distance != 0) {
    std::pair<double, double> f = {0, 0};
    double sforce = springConstant * (distance - springRestLength);    // spring force is linear with seperation (F = k*d)

    f.first = sforce * (deltaX / distance);         //x component of force  (cos(theta))
    f.second = sforce * (deltaY / distance);        //y component of force  (sin(theta))
    
    if (deltaX < 0) {                               // may revisit this approach
      forces[node1].first += f.first;               // if deltaX from node1 -> node2 is negative, attractive spring force should point in +x for node1 and -x for node2
      forces[node2].first -= f.first;
    } else {
      forces[node1].first -= f.first;
      forces[node2].first += f.first;         
    }

    if (deltaY < 0) {
      forces[node1].second += f.second;              //same for y
      forces[node2].second += f.second;
    } else {
      forces[node1].second += f.second;
      forces[node2].second += f.second;
    }
  }

  return;
 
}
void Forcegraph::repelNodes(int node1, int node2, double coulombConstant) {
  //use Coulomb's Law


  double deltaX = pos[node1].first - pos[node2].first;
  double deltaY = pos[node1].second - pos[node2].second;

  double distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);


  std::pair<double, double> f = {0, 0};

  if (distance == 0) {
    f = {std::rand() % 100, std::rand() % 100}; // idk
  } else {
    double cForce = coulombConstant / (distance * distance);      // coulomb constant could depend on actual data? force is currently just based on distance between vertices
    f.first = cForce * deltaX / distance;
    f.second = cForce * deltaY / distance;
  }

  if (deltaX < 0) {                                                       
    forces[node1].first += f.first;               
    forces[node2].first -= f.first;
  } else {
    forces[node1].first -= f.first;
    forces[node2].first += f.first;         
  }

  if (deltaY < 0) {
    forces[node1].second += f.second;            
    forces[node2].second += f.second;
  } else {
    forces[node1].second += f.second;
    forces[node2].second += f.second;
  }

  return;
}

void Forcegraph::updatePositions(double deltaT) {

  for (int i = 0; i < numVertices; i++) {

    double deltaX = deltaT * forces[i].first;
    double deltaY = deltaT * forces[i].second;

    pos[i].first += deltaX;                             // simplified time evolution of forces, not sure how we would implement a more realistic case
    pos[i].second += deltaY;
  }
}




cs225::PNG Forcegraph::createGraphic(int w, int h) {


   cs225::PNG *png = new PNG(w, h);

   for (int i = 0; i < w; i++) {
     for (int j = 0; j < h; j++) {

       HSLAPixel & curpix = png->getPixel(i, j);
        //....
     }
   }


  // draw circles for nodes, sizes based on data maybe?
  // lines for edges
  
  
}



/**
Algorithm:
  1. Make random placements for all nodes
  2. repelNodes: repel every node from every other node
  3. if nodes are connected: attractNodes
  4. check equilibrium
  5. if not in equilibrium repeat
  6. print graph (will use circles for nodes and lines for edges)
*/
