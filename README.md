# Analyzing Twitch data through PageRank and Force-Directed Graphs

## Code Structure

All of our data are stored under `.csv` files. Test files are labeled as such, and have less information than the original data files. They are to serve as smaller, but relevant data sets for testing. 

For storing our graph data, we created a graph class. This will be used to process and store information retrieved from the `.csv` files. 

For both our algorithms, we have seperate class files that will have a primary input of a graph class instance.  

## Testing

As our algorithms becoming increasingly more complex and in need of edge testing, we will be implementing catch2. As of now, we have a state manager labaled `TEST_STATE` in `main.cpp` that allows us to toggle from debugging/development to production modes. 

As of now, our primary way of testing is to `std::cout` our results, as a large portion of this project is visual. We can test our math for PageRank manually using the `std::cout` results as our datasets are small enough to allow us to do so. 

## Execution Commands

In preparation to run project, use the command `make` to compile our project. 

Once the project is compiled, used the command `./test_make` to execute our project. 

--- 


armaanm3-ivette2-rar4-mateojc2

