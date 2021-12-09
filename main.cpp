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

        unsigned int w = 800;
        unsigned int h = 600;
        
        f.setup(g, 1.0, 50.0, 1000.0, 1.0, 100, w, h);

        std::cout << "1" << std::endl;

    }
   
    

    return 0;
}