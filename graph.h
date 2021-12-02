/**
 * @file graph.h
 * Definition of a class for a graph
 */

#pragma once
#include <string>
#include <vector>
#include <map>


class Graph {
    public:
        Graph(std::string, std::string);
        bool is_connected(int node1, int node2);
        std::vector<int> BFS(int start);
        void test();
        std::vector<std::vector<double>> amatrix;


    private:
        // Private variables
        int numVertices;
        std::vector<std::vector<bool>> adjacency_matrix;
        // id, views (important/relevant data)
        std::map<int, int> data;

        // Helper functions
        // String, token to split at
        std::vector<std::string> split(std::string, std::string);
        void printAdjacencyMatrix(int size);
        std::vector<double> viewcount;
};
