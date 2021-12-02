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

void Forcegraph::attractNodes(int node1, int node2){
  //use Hooke's Law
}

void Forcegraph::repelNodes(int node1, int node2){
  //use Coulomb's Law
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
