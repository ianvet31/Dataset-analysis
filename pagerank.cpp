/**
 * @file pagerank.cpp
 * Implementation of the pagerank algorithm.
 */

#include "pagerank.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <vector>

using namespace std;

Pagerank::Pagerank() {
    
}

void Pagerank::setupPageRank(Graph & graph) {

    std::cout << "graph is passed" << graph.amatrix[0][0] << std::endl;

    for (size_t i = 0; i < graph.amatrix.size(); i++) {
        int count = 0;

        // BUG: j was unbounded 
        for (size_t j = 0; j < graph.amatrix.size(); j++) {
            if (graph.amatrix[j][i]) {
                count++;
            }
        }
        if (!count) {
            for (size_t j = 0; j < graph.amatrix.size(); j++) {
                if (graph.amatrix[j][i]) {
                    graph.amatrix[j][i] = double(1)/double(graph.amatrix.size());
                }
            }
        } else {
            for (size_t j = 0; j < graph.amatrix.size(); j++) {
                graph.amatrix[j][i] = double(graph.amatrix.size())/double(count);
            }
        }
    }
    return;
}



void Pagerank::printAMatrix(Graph & graph, int size)
{
    std::cout << "\n";
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            std::cout << graph.amatrix[i][j] << "    ";
        }
        std::cout << "\n";
    }
}