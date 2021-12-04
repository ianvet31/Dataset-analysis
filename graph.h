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
        std::vector<std::vector<double>> amatrix;


        int get_numVertices();
        std::map<int, int> get_data();

        // Used for debugging
        void test();

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
