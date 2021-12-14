# Analyzing Twitch data through PageRank and Force-Directed Graphs

## Code Structure

All of our data are stored under `.csv` files. Test files are labeled as such, and have less information than the original data files. They are to serve as smaller, but relevant data sets for testing. The full test data can be found in the Stanford Data Collection. The medium files were used for our force-directed graph, and it contains around 1000 users. The large files were used for the Page Rank algorithm, and contain around 10000 users.

For storing our graph data, we created a graph class. This will be used to process and store information retrieved from the `.csv` files. 

For both our algorithms, we have seperate class files that will have a primary input of a graph class instance.  

## Testing

For the less complicated parts of our project, such as the BFS traversal and creation of the graph, we used print statements. This made it easy to see if the adjacency matrix was working correctly, and allowed a direct comparison for the BFS. This was also helpful, as the majority of our testing was easier with visuals.

As our algorithms became increasingly more complex and in need of edge testing, we implemented catch2. There are also seperate tests for both the Page Rank and the Force-Dierected graph algorithms.

These tests can be compiled using 'make test' and run using ./test.

## Execution Commands

In preparation to run project, use the command `make` to compile our project. 

Once the project is compiled, used the command `./test_make` to execute our project. 

--- 


armaanm3-ivette2-rar4-mateojc2

