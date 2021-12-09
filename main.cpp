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

    bool TEST_STATE = true;

    if (TEST_STATE) {
        Graph g = Graph("users_test_data.csv", "edges_test_data.csv");
        // g.test();
        Pagerank p = Pagerank();
        p.setupPageRank(g);
        p.printAMatrix(g, g.amatrix.size());
        p.printAMatrix(g, g.amatrix.size());
        std::cout << "setup page rank" << std::endl;

        Forcegraph f = Forcegraph();
        f.setup(g, 5.0, 5.0, 5.0, 1.0, 800, 600, 300);

        

    }
   
    

    return 0;
}