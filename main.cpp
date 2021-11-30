#include "graph.h"

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

    bool TEST_STATE = true;

    if (TEST_STATE) {
        Graph g = Graph("users_test_data.csv", "edges_test_data.csv");
        g.test();
    }
   
    

    return 0;
}