/**
 * @file forcegraph.cpp
 * Implementation of force-directed graph algorithm
 */

#include "forcegraph.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <vector>
#include <math.h>
#include "cs225/PNG.h"
using cs225::PNG;
#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;



Forcegraph::Forcegraph() {

}

// Sets initial parameters, executes forces and creates output graphics

void Forcegraph::setup(Graph graph, double springconst, double springlen, double coulombconst, double delta_time, int max_i, unsigned w, unsigned h) {
    srand(time(NULL));
    width = w;
    height = h;
    numVertices = graph.get_numVertices();
    data = graph.get_data();


    pos.resize(numVertices, {0, 0});
    forces.resize(numVertices, {0, 0});

    assign_Positions();
  
    applyForces(graph, springconst, springlen, coulombconst, delta_time, max_i);

 
    std::cout << "done setup" << std::endl;


    node_graphics();
    createGraphic(graph);

    return;
}

// Applies spring and coulomb forces for each iteration, checks if equilibrium has been reached each time
// Stops at some max_iter if equilibrium is still not reached

void Forcegraph::applyForces(Graph g, double springconst, double springlen, double coulombconst, double delta_time, int max_iter) {
  for (int i = 0; i < max_iter; i++) {
    
    repelNodes(coulombconst);
    attractNodes(g, springconst, springlen);
    updatePositions(delta_time);

    if (equilibrium_check()) {
      break;
    }


  }
}

// Equilibrium check is run at the end of each iteration, checks if the forces of each node is minimized (approx. zero)

bool Forcegraph::equilibrium_check() { 

  for (int i = 0; i < numVertices; i++) {
    if (!(abs(forces[i].first) < 1) || !(abs(forces[i].second) < 1)) {
      return false;
    }
  }
  return true;

}


// Assigns completely random positions for nodes


void Forcegraph::assign_Positions() {

    for (int i = 0; i < numVertices; i++) {
      pos[i] = {std::rand() % (width - 400) + 400, std::rand() % (height - 300) + 300}; 
    }

}

// Spring force function
// Loops through every pair of nodes, checks if they're connected
// The appliced force can be attractive or repulsive based on the spring rest length
// Force is linear with distance between nodes as F = k*d
 
void Forcegraph::attractNodes(Graph g, double springConstant, double springRestLength) {
  //use Hooke's Law

  for (int i = 0; i < numVertices; i++) {
    for (int j = i + 1; j < numVertices; j++) {


      if (i == j) {
        continue;
      }

      if (!g.is_connected(i, j)) {
        continue;
      }

  
      double deltaX = pos[j].first - pos[i].first;
      double deltaY = pos[j].second - pos[i].second;

      double distance = sqrt(deltaX * deltaX + deltaY * deltaY);



      if (distance != 0) {
        std::pair<double, double> force = {0, 0};
        double sforce = springConstant * (distance - springRestLength);    

       force.first = sforce * (deltaX / distance);         //x component of force  (cos(theta))
       force.second = sforce * (deltaY / distance);        //y component of force  (sin(theta))
    

      forces[i].first += force.first;               
      forces[i].second += force.second;
      forces[j].first -= force.first;               
      forces[j].second -= force.second;
       
      }
    }
  }
}


// Repulsive force function, uses Couloumb's law for charged particles (F = c / d^2)
// Doesn't care about edges, each node is repulsed from every other node

void Forcegraph::repelNodes(double coulombConstant) {
  for (int i = 0; i < numVertices; i++) {
    for (int j = i + 1; j < numVertices; j++) {

      double deltaX = pos[j].first - pos[i].first;
      double deltaY = pos[j].second - pos[i].second;

      double distance = sqrt(deltaX * deltaX + deltaY * deltaY);


      std::pair<double, double> force = {0, 0};

      if (distance < 50) {
        pos[i] = {std::rand() % (width - 50) + 50, std::rand() % (height - 50) + 50};
        pos[j] = {std::rand() % (height - 50) + 50, std::rand() % (height - 50) + 50};
        continue;

      } else {
       double cForce = coulombConstant / (distance * distance); 
        force.first = cForce * (deltaX / distance);
        force.second = cForce * (deltaY / distance);
      }

      forces[i].first += force.first;               
      forces[i].second += force.second;
      forces[j].first -= force.first;               
      forces[j].second -= force.second;

    }
  }

  
}

// Updates the positions of nodes based on their x and y force values and a time step deltaT
// If the force is pushing the node out of range for the PNG, it hits a wall and cannot be pushed further

void Forcegraph::updatePositions(double deltaT) {

  double max_move = 10;

  for (int i = 0; i < numVertices; i++) {

    double deltaX = deltaT * forces[i].first;
    double deltaY = deltaT * forces[i].second;

    double dist = sqrt(deltaX * deltaX + deltaY * deltaY);

    if (dist > max_move) {
      deltaX *= (max_move / dist);
      deltaY *= (max_move / dist);

    }



    if (((pos[i].first + deltaX) < (width - 50)) && ((pos[i].first + deltaX) > 50)) {
      pos[i].first += deltaX;     
    } else {
      pos[i].first = rand() % (width - 400) + 400;
    }
    if (((pos[i].second + deltaY) < (height - 50)) && ((pos[i].second + deltaY) > 50)) {
      pos[i].second += deltaY;    
    } else {
      pos[i].second = rand() % (height - 300) + 300;
    }
  }
}

// Assigns parameters based on a streamer's view count
// First parameter: hue of node (higher viewcounts are red, lower viewcounts are blue)
// Second parameter: radius of node (node circle graphic, size scaled with viewcount)

void Forcegraph::node_graphics() {

  node_params.resize(numVertices, {0, 0});

  for (int i = 0; i < numVertices; i++) {
     int viewcount = data.at(i);
     if (viewcount > 10000000) {
       node_params[i].first = 0.0;
       node_params[i].second = 20.0;
     } else if (viewcount > 1000000) {
       node_params[i].first = 20.0;
       node_params[i].second = 10.0;
     } else if (viewcount > 100000) {
       node_params[i].first = 45.0;
       node_params[i].second = 7.0;
     } else if (viewcount > 1000) {
       node_params[i].first = 65.0;
       node_params[i].second = 4.0;
     } else {
       node_params[i].first = 90.0;
       node_params[i].second = 2.0;
     }
   }
   

}

// Creates an output PNG using the cs225 PNG and HSLAPixel classes
// First draws edges between all connected nodes
// Next draws nodes from end positions after forces have been applied, graphics based on node parameters

void Forcegraph::createGraphic(Graph g) {

  cs225::PNG png(width, height);
  for (int j = 0; j < numVertices; j++) {
      for (int k = j + 1; k < numVertices; k++) {
        if (g.is_connected(j, k)) {

            double node_1x = pos[j].first;
            double node_1y = pos[j].second;
            double node_2x = pos[k].first;
            double node_2y = pos[k].second;

            double dX = node_2x - node_1x;
            double dY = node_2y - node_1y;

        
            unsigned start_x = 0;
            unsigned start_y = 0;
            unsigned end_x = 0;
            unsigned end_y = 0;
            double slope = 0;

            if (dX > 0) {
              start_x = (unsigned int) node_1x;
              start_y = (unsigned int) node_1y;
              end_x = (unsigned int) node_2x;
              end_y = (unsigned int) node_2y;
              slope = dY / dX;
        
            } 
            if (dX < 0) {
              start_x = (unsigned int) node_2x;
              start_y = (unsigned int) node_2y;
              end_x = (unsigned int) node_1x;
              end_y = (unsigned int) node_1y;
              slope = dY / dX;
            }
            
            double y = start_y;
            for (unsigned x = start_x; x < end_x; x++) {
              cs225::HSLAPixel & curpix = png.getPixel(x, (unsigned) y);
              curpix.h = 0.0;
              curpix.s = 1.0;
              curpix.l = 0.0;
              y += slope;
            }


            
        }
      }
   }

  for (int i = 0; i < numVertices; i++) {
    double node_x = pos[i].first;
    double node_y = pos[i].second;
    

    for (unsigned  j = 0; j < png.width(); j++) {
      for (unsigned  k = 0; k < png.height(); k++) {

       cs225::HSLAPixel & curpix = png.getPixel(j, k);
       double radius = sqrt((node_x - j)*(node_x - j)+(node_y - k)*(node_y - k));

       if (radius < node_params[i].second) {
         curpix.h = node_params[i].first;
         curpix.s = 1.0;
         curpix.l = 0.5;

       } else {
         continue;
       }
       
     }
   }
  }
  png.writeToFile("FDG_out.png");
}

std::vector<std::pair<double, double>> Forcegraph::get_pos() {
  return pos;
}
std::map<int, int> Forcegraph::get_data() {
  return data;
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
