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
    bool TEST_STATE = true;
    
    if (DEMO_PAGERANK_STATE_) {
        Graph g = Graph("large_twitch_features.csv", "large_twitch_edged.csv");
        Pagerank p = Pagerank();
        p.powerPageRank(g, 10);
    }
    if (TEST_STATE) {
	std::cout << "Creating Graph..." << std::endl;
        Graph g = Graph("users_test_data.csv", "edges_test_data.csv");

        
        

        Forcegraph f = Forcegraph();

        unsigned int w = 1600;
        unsigned int h = 900;

        // FDG args: graph g, spring constant, spring rest length, coulomb constant, time step (delta T), max # of iterations, width and height of output
 	std::cout << "Setting up force-directed graph..." << std::endl;       
        f.setup(g, 5, 100., 100., 0.001, 1000, w, h);  // FDG parameters are fairly sensitive, equilibrium can usually be achieved with small spring const (~10^-2) and large coulomb (~10^4)

    }
   
    

    return 0;
}
