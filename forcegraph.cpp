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



//todo - more setup, fix force functions, add equilibrium check, add graphics


// update positions over some delta_time for iterations, equil check each time
Forcegraph::Forcegraph() {

}

void Forcegraph::setup(Graph graph, double springconst, double springlen, double coulombconst, double delta_time, int max_i, unsigned w, unsigned h) {   // will want to assign nodes color, size, etc.
    srand(time(NULL));
    width = w;
    height = h;
    numVertices = graph.get_numVertices();
    data = graph.get_data();


    pos.resize(numVertices, {0, 0});
    forces.resize(numVertices, {0, 0});

    assign_Positions();


   // std::cout << pos[1].first << std::endl;
   // std::cout << pos[1].second << std::endl;

    //std::cout << pos[2].first << std::endl;
    //std::cout << pos[2].second << std::endl;

   // std::cout << pos[3].first << std::endl;
    //std::cout << pos[3].second << std::endl;





  
    applyForces(graph, springconst, springlen, coulombconst, delta_time, max_i);

 

    std::cout << "done setup" << std::endl;


    node_graphics();
    createGraphic(graph);





    return;
}

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

bool Forcegraph::equilibrium_check() {        // confirms that x and y components of force are zero for each node

  for (int i = 0; i < numVertices; i++) {
    if (!(abs(forces[i].first) < 1) || !(abs(forces[i].second) < 1)) {
      return false;
    }
  }
  return true;

}


// Assigns completely random positions for nodes, maybe change later


void Forcegraph::assign_Positions() {

    for (int i = 0; i < numVertices; i++) {
      pos[i] = {std::rand() % (width - 50) + 50, std::rand() % (height - 50) + 50}; 
    }

}
// std::rand() % width

// maybe change force functions to loop through all nodes, not two at a time..
 
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
        std::pair<double, double> f = {0, 0};
        double sforce = springConstant * (distance - springRestLength);    // spring force is linear with seperation (F = k*d)

       f.first = sforce * abs(deltaX / distance);         //x component of force  (cos(theta))
       f.second = sforce * abs(deltaY / distance);        //y component of force  (sin(theta))
    
       
       if (deltaX < 0) {                                                       
        forces[i].first -= f.first;               
        forces[j].first += f.first;
       } else {
        forces[i].first += f.first;
        forces[j].first -= f.first;         
       }

        if (deltaY < 0) {
          forces[i].second -= f.second;            
          forces[j].second += f.second;
        } else {
          forces[i].second += f.second;
          forces[j].second -= f.second;
        }
      }
    }
  }
}
void Forcegraph::repelNodes(double coulombConstant) {
  //use Coulomb's Law
  for (int i = 0; i < numVertices; i++) {
    for (int j = i + 1; j < numVertices; j++) {

      double deltaX = pos[j].first - pos[i].first;
      double deltaY = pos[j].second - pos[i].second;

      double distance = sqrt(deltaX * deltaX + deltaY * deltaY);


      std::pair<double, double> f = {0, 0};

      if (distance < 10) {
        pos[i] = {std::rand() % (width - 50) + 50, std::rand() % (height - 50) + 50};
        pos[j] = {std::rand() % (width - 50) + 50, std::rand() % (height - 50) + 50};
        continue;

      } else {
       double cForce = coulombConstant / (distance * distance);      // coulomb constant could depend on actual data? force is currently just based on distance between vertices
        f.first = cForce * abs(deltaX / distance);
        f.second = cForce * abs(deltaY / distance);
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

    std::cout << forces[i].first << std::endl;
    std::cout << forces[i].second << std::endl;

    if (((pos[i].first + deltaX) < 750) && ((pos[i].first + deltaX) > 50)) {
      pos[i].first += deltaX;     
    } else if (deltaX > 0) {
      pos[i].first = 749;
    } else {
      pos[i].first = 51;
    }
    if (((pos[i].second + deltaY) < 550) && ((pos[i].second + deltaY) > 50)) {
      pos[i].second += deltaY;    
    } else if (deltaY > 0) {
      pos[i].second = 549;
    } else {
      pos[i].second = 51;
    }
  }
}



void Forcegraph::node_graphics() {

  node_params.resize(numVertices, {0, 0});

  for (int i = 0; i < numVertices; i++) {
     int viewcount = data.at(i);
     if (viewcount > 10000000) {
       node_params[i].first = 0.0;
       node_params[i].second = 30.0;
     } else if (viewcount > 1000000) {
       node_params[i].first = 20.0;
       node_params[i].second = 20.0;
     } else if (viewcount > 100000) {
       node_params[i].first = 45.0;
       node_params[i].second = 15.0;
     } else if (viewcount > 1000) {
       node_params[i].first = 65.0;
       node_params[i].second = 10.0;
     } else {
       node_params[i].first = 90.0;
       node_params[i].second = 5.0;
     }
   }
   

}

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


            
        } else {

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
        
  
       }
       
     }
   }
  }

    

   

  png.writeToFile("FDG_out.png");




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
