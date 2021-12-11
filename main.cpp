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

        unsigned int w = 1600;
        unsigned int h = 900;

        // FDG args: graph g, spring constant, spring rest length, coulomb constant, time step (delta T), max # of iterations, width and height of output
        
        f.setup(g, 0.05, 250., 10000.0, 1.0, 100, w, h);  // FDG parameters are fairly sensitive, equilibrium can usually be achieved with small spring const (~10^-2) and large coulomb (~10^4)

    }
   
    

    return 0;
}