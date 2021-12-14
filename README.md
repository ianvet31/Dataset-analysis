
# Analyzing Twitch data through PageRank and Force-Directed Graphs

## Code Structure

All of our data are stored under `.csv` files. Test files are labeled as such, and have less information than the original data files. They are to serve as smaller, but relevant data sets for testing. The full test data can be found in the Stanford Data Collection. The medium files were used for our force-directed graph, and it contains around 1000 users. The large files were used for the Page Rank algorithm, and contain around 10000 users.

For storing our graph data, we created a graph class. This will be used to process and store information retrieved from the `.csv` files. 

For both our algorithms, we have seperate class files that will have a primary input of a graph class instance.  

## Testing

For the less complicated parts of our project, such as the BFS traversal and creation of the graph, we used print statements. This made it easy to see if the adjacency matrix was working correctly, and allowed a direct comparison for the BFS. This was also helpful, as the majority of our testing was easier with visuals.

As our algorithms became increasingly more complex and in need of edge testing, we implemented catch2. There are also seperate tests for both the Page Rank and the Force-Dierected graph algorithms.

These tests can be compiled using `make test` and run using `./test.`

## Inputs and Outputs

The inputs and outputs for our project are not controlled by the user on the command line. To change any inputs and outputs, the user must go into the files.

In order to change the `.csv` files used for the project, open `main.cpp` and edit the Graph constructor. The first parameter hold the node data, and the second holds the edge data.

In order to print the BFS and Adjacency matrix, add `g.test()` to `main.cpp` in the TEST_STATE section.

To control which algorithms are run, change the boolean vaues in `main.cpp`. To only run Page Rank, set TEST_STATE to false. To only run the Force-Directed graph, set DEMO_PAGERANK_STATE to false. Different `.csv` files can be used for the algorithms, but they can still run at the same time.

### PAGERANK USAGE
Modify the information between the brackets to use different data files. 
`Graph g = Graph("{USERS_DATA}.csv", "{EDGES_DATA}.csv");`

Modify the number of iterations by changing the default number iterations (100). 
`p.powerPageRank(g, {num_iterations});`

The damping factor (default .85) can be modified from within the pagerank.cpp file.
`damping(graph, {damping_factor})`

Results:
The adjacency matrix for the graph is outputted to currentamatrix.txt
The pagerank leaderboard with sorted weights assigned to users is outputted to pagerank_leaderboard.txt.
 
 
 #FORCE DIRECTED GRAPH USAGE#
        Graph g = Graph("{USERS DATA}.csv", "{EDGES DATA}.csv"); // modify {} appropriately, note that data with > 1000 nodes will run slowly
        Forcegraph f = Forcegraph(); // empty constructor
        f.setup(g, double spring_constant, double spring_rest_length, double coulomb_constant, double delta_t, int max_iterations, unsigned width, unsigned height); // sets up and runs force graph algorithm
        The forcegraph output can be fairly sensitive to its setup parameters. For the majority of our testing, we used a 1600x1600 square PNG canvas and found the best results with the following parameters: spring_constant = 5.0, spring_rest_length = 100.0, coulomb_constant = 20000.0, delta_t = 0.0001, max_iterations = 1000
        Running the setup function with full parameters will run the full algorithm and save the output PNG to the location "FDG_output.png"

## Tests
### Pagerank Tests
Multiple tests were created to test every aspect of every helper function used in for the Pagerank algorithm.
  - validSquareMatrix (checks that rows == cols(rows for every row)
  - validMarkovMatrix (checks that the sum of columns is equal to 1)
  - unitVectorGeneration (checks that the randomunitvector is a unit vector)
  - matrixMultiplication basic (tests smaller 2d matrix multiplied by 1d matrix)
  - matrixMultiplication advanced (tests larger 2d matrix multiplied by 1d matrix)
  - finalPagerankSum (must equal to 1)
 
## Execution Commands

In preparation to run project, use the command `make` to compile our project. 

Once the project is compiled, used the command `./test_make` to execute our project. 

--- 


armaanm3-ivette2-rar4-mateojc2

