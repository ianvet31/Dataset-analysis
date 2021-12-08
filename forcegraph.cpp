/**
 * @file forcegraph.cpp
 * Implementation of force-directed graph algorithm
 */

#include "forcegraph.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <vector>
#include <math.h>
#include <cs225/PNG.h>
#include <cs225/HSLAPixel.h>


//todo - more setup, fix force functions, add equilibrium check, add graphics


// update positions over some delta_time for iterations, equil check each time



void Forcegraph::setup(Graph & graph, double springconst, double springlen, double coulombconst, double delta_time) {   // will want to assign nodes color, size, etc.

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
    applyForces(springconst, springlen, coulombconst, delta_time);

    createGraphic(800, 600);





    return;
}

void Forcegraph::applyForces(double springconst, double springlen, double coulombconst, double delta_time) {
  assign_Positions();
  while (!equilibrium_check()) {
    attractNodes(springconst, springlen);
    repelNodes(coulombconst);
    updatePositions(delta_time);


  }
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
 
void Forcegraph::attractNodes(double springConstant, double springRestLength) {
  //use Hooke's Law

  for (int i = 0; i < numVertices; i++) {
    for (int j = i + 1; j < numVertices; j++) {

      if (!g.is_connected(i, j)) {
        continue;
      }
  
      double deltaX = pos[i].first - pos[j].first;
      double deltaY = pos[i].second - pos[j].second;

      double distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);


      if (distance != 0) {
        std::pair<double, double> f = {0, 0};
        double sforce = springConstant * (distance - springRestLength);    // spring force is linear with seperation (F = k*d)

       f.first = sforce * (deltaX / distance);         //x component of force  (cos(theta))
       f.second = sforce * (deltaY / distance);        //y component of force  (sin(theta))
    
       if (deltaX < 0) {                                                       
        forces[i].first += f.first;               
        forces[j].first -= f.first;
       } else {
        forces[i].first -= f.first;
        forces[j].first += f.first;         
       }

        if (deltaY < 0) {
          forces[i].second += f.second;            
          forces[j].second -= f.second;
        } else {
          forces[i].second -= f.second;
          forces[j].second += f.second;
        }
      }
    }
  }
}
void Forcegraph::repelNodes(double coulombConstant) {
  //use Coulomb's Law
  for (int i = 0; i < numVertices; i++) {
    for (int j = i + 1; j < numVertices; j++) {

      double deltaX = pos[i].first - pos[j].first;
      double deltaY = pos[i].second - pos[j].second;

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
        forces[i].first += f.first;               
        forces[j].first -= f.first;
      } else {
        forces[i].first -= f.first;
        forces[j].first += f.first;         
      }

      if (deltaY < 0) {
        forces[i].second += f.second;            
        forces[j].second -= f.second;
      } else {
        forces[i].second -= f.second;
        forces[j].second += f.second;
      }

    }
  }

  
}

void Forcegraph::updatePositions(double deltaT) {

  for (int i = 0; i < numVertices; i++) {

    double deltaX = deltaT * forces[i].first;
    double deltaY = deltaT * forces[i].second;

    pos[i].first += deltaX;                             // simplified time evolution of forces, not sure how we would implement a more realistic case
    pos[i].second += deltaY;
  }
}



void Forcegraph::node_graphics() {

  for (int i = 0; i < numVertices; i++) {
     int viewcount = data.at(i);
     if (viewcount > 10000000) {
       node_params[i].first = 0.0;
       node_params[i].second = 10.0;
     } else if (viewcount > 1000000) {
       node_params[i].first = 20.0;
       node_params[i].second = 7.0;
     } else if (viewcount > 100000) {
       node_params[i].first = 45.0;
       node_params[i].second = 5.0;
     } else if (viewcount > 1000) {
       node_params[i].first = 65.0;
       node_params[i].second = 3.0;
     } else {
       node_params[i].first = 90.0;
       node_params[i].second = 1.0;
     }
   }
   

}

cs225::PNG Forcegraph::createGraphic(int w, int h) {

  node_graphics();

  cs225::PNG *png = new cs225::PNG(w, h);


  for (int i = 0; i < numVertices; i++) {
    for (int j = 0; i < w; i++) {
      for (int k = 0; j < h; j++) {

       std::pair<double, double> curr_pos = pos[i];
       cs225::HSLAPixel & curpix = png->getPixel(i, j);

       double radius = sqrt((j - curr_pos.first)*(j - curr_pos.first) + (k - curr_pos.second)*(k - curr_pos.second));

       if (radius < node_params[i].second) {
         curpix.h = node_params[i].first;
         curpix.s = 1.0;
         curpix.l = 0.5;

       } else {
         curpix.h = 0.0;
         curpix.s = 0.0;
         curpix.l = 1.0;
       }
       
     }
   }

  }

  png->writeToFile("FDG_out.png");


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
