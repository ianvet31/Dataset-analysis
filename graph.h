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
        void test();

    private: 
        // Private variables

        std::vector<std::vector<double>> adjacency_matrix;
        // id, views (important/relevant data)
        std::map<int, int> data;

        // Helper functions
        // String, token to split at
        std::vector<std::string> split(std::string, std::string);
};  