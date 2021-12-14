#include "graph.h"
#include "pagerank.h"
#include "forcegraph.h"
#include "iostream"

int main() {

    bool DEMO_PAGERANK_STATE_ = true;
    bool TEST_STATE = true;
    
    if (DEMO_PAGERANK_STATE_) {
        Graph g = Graph("users_test_data.csv", "edges_test_data.csv");
        Pagerank p = Pagerank();
        p.powerPageRank(g, 100);
    }
    if (TEST_STATE) {
	std::cout << "Creating Graph..." << std::endl;
        Graph g = Graph("medium_features.csv", "medium_edges.csv");

        //p.printAMatrix(g, g.amatrix.size());
        std::cout << "Setting up Page Rank..." << std::endl;

        Forcegraph f = Forcegraph();

        unsigned int w = 1600;
        unsigned int h = 1600;

        // FDG args: graph g, spring constant, spring rest length, coulomb constant, time step (delta T), max # of iterations, width and height of output
 	std::cout << "Setting up force-directed graph..." << std::endl;       
        f.setup(g, 5.0, 100., 20000, 0.0001, 1000, w, h);  // FDG parameters are fairly sensitive, equilibrium can usually be achieved with small spring const (~10^-2) and large coulomb (~10^4)

    }
   
    

    return 0;
}
