/**
 * @file pagerank.h
 * Definition of a class for the pagerank algorithm 
 */

#pragma once
#include <string>
#include <vector>
#include <map>
#include "Graph.h"

class Pagerank {
    public:
        void setupPageRank(Graph & graph);
        void printAMatrix(Graph & graph, int size);
    private:
        // Private variables

};
