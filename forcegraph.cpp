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

//todo - more setup, fix force functions, add equilibrium check, add graphics


// will want to assign nodes color, size, etc.

void Forcegraph::setup(Graph & graph) { 
    for (size_t i = 0; i < graph.amatrix.size(); i++) {
        for (size_t j = 0; i < graph.amatrix.size(); j++) {
            if (graph.amatrix[j][i]) {
                numVertices++;
            }
        }
    }
    return;
}


// Assigns completely random positions for nodes, maybe change later
// currently will cause graphic overlapping

void Forcegraph::assign_Positions() {

    pos.resize(numVertices, {0, 0});
    forces.resize(numVertices, {0, 0});

    for (int i = 0; i < numVertices; i++) {
      pos.push_back(std::make_pair(std::rand() % width, std::rand() % height));
    }

}
 
void Forcegraph::attractNodes(int node1, int node2) {
  //use Hooke's Law

  double springConstant = 0.0;

  double deltaX = abs(get_xpos(node1) - get_xpos(node2));           // maybe easier to use different coordinate system (polar)
  double deltaY = abs(get_ypos(node1) - get_ypos(node2));

  double distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

  if (distance != 0) {
    std::pair<double, double> f = {0, 0};
    double force = springConstant * (distance - springRestLength);    // spring force is linear with seperation (F = k*d)
    f.first = force * deltaX / distance;
    f.second = force * deltaY / distance;
    
    forces[node1].first += f.first;
    forces[node1].second += f.second;
    forces[node2].first -= f.first;
    forces[node2].second -= f.second;
  }
 
}
void Forcegraph::repelNodes(int node1, int node2) {
  //use Coulomb's Law

  // Assumes nodes are connected, need to implement if

  for (int j = 0; j < numVertices; j++) {
    for (int k = j + 1; k < numVertices; k++) {

      double deltaX = pos[j].first - pos[k].first;
      double deltaY = pos[j].second - pos[k].second;
      double dist = std::sqrt(deltaX * deltaX + deltaY * deltaY);

      std::pair<double, double> f = {0, 0};

      if (dist == 0) {
        f = {std::rand() % 100, std::rand() % 100}; // idk
      } else {
        double tempF = coulomb_constant / (dist * dist);
        f.first = tempF * deltaX / dist;
        f.second = tempF * deltaY / dist;
      }

      forces[j].first -= f.first;
      forces[j].second -= f.second;
      forces[k].first += f.first;
      forces[k].second += f.second;
    }
  }

  return;
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
