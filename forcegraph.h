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
  private:
    //private vars/functions
};
