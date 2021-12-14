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
        // Constructor
        Graph(std::string, std::string);
        
        // Public Matrix used for Pagerank
        std::vector<std::vector<double>> amatrix;
    
        // Helper Functions
        // Determines if two nodes/users have mutual following
        bool is_connected(int node1, int node2);
        // BFS
        std::vector<int> BFS(int start);
        
        // Getters
        std::map<int, int> get_data();
        int get_numVertices();

        // Used for debugging
        void test();

    private:
        // Private variables
        // Verticies in graph
        int numVertices;
        // Initialized adjacency matrix. Used in both Pagerank and FDG
        std::vector<std::vector<bool>> adjacency_matrix;
        // Maps user id to views
        std::map<int, int> data;
        // Used in BFS    
        std::vector<double> viewcount;

        // Helper functions
        // Parses string into seperate strings given splitting token
        std::vector<std::string> split(std::string, std::string);
        // Used for debugging
        void printAdjacencyMatrix(int size);
};
