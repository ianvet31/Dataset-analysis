#include "graph.h"
#include "pagerank.h"
#include "forcegraph.h"
#include "iostream"

int main() {
    // main
        // constructs graph
    // tests
    // graph class  
        // constructor: file name for data, file name for edges
            // reads data and stores data
            // private
                // users
                // adjency matrix (double values bc for pageRank)
        // outputVisual()
        // output most probable user()

    bool DEMO_PAGERANK_STATE_ = true;

    if (DEMO_PAGERANK_STATE_) {
        Graph g = Graph("users_test_data.csv", "edges_test_data.csv");
        Pagerank p = Pagerank();
        p.powerPageRank(g, 100);

    }
   
    

    return 0;
}