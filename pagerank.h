/**
 * @file pagerank.h
 * Definition of a class for the pagerank algorithm 
 */

#pragma once
#include <string>
#include <vector>
#include <map>
#include "graph.h"

/**
 * Pagerank algorithm based on power iteration and damping.
 */
using namespace std;
class Pagerank {
    public:
        Pagerank();
        void setupPageRank(Graph &graph);
        void randomunitvectorgenerator(Graph &graph);
        void damping(Graph &graph, double damping);
        void powerPageRank(Graph &graph, int iterations);
        void print1dvector(vector<double> vec);
        vector<double> matrixmultiplication(vector<vector<double>> d2v, vector<double> d1v);
        void printAmatrix(Graph &graph);
        void leaderboardSortPrint(vector<double> vec);
        static bool sortHelper(const vector<double>& v1, const vector<double>& v2);
        vector<double> getRandomUnitVector();

    private:
        // Private variables
        vector<double> randomunitvector;

};
