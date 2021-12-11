/**
 * @file graph.cpp
 * Implementation of the graph class.
 */

#include "graph.h"
#include <string>
#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <list>
#include <queue>



Graph::Graph(std::string datafile, std::string edgefile)
{
    std::ifstream fileData(datafile);
    std::ifstream fileEdges(edgefile);
    numVertices = 0;

    if (fileData.is_open())
    {
        std::istream_iterator<std::string> data_iter(fileData);
        // Ignore first line
        ++data_iter;
        while (!fileData.eof())
        {
            // views,mature,life_time,created_at,updated_at,numeric_id,dead_account,language,affiliate
            // 0     1      2         3          4          5          6            7        8
            std::vector<std::string> lineData = split(*data_iter, ",");
            // id, views
            data.insert({std::stoi(lineData[5]), std::stoi(lineData[0])});

            numVertices++;
            ++data_iter;
        }
    }
    //set up adjacency matrix
    adjacency_matrix.resize(numVertices + 1, std::vector<bool>(numVertices + 1));
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            adjacency_matrix[i][j] = 0;
        }
    }

    if (fileEdges.is_open())
    {
        std::istream_iterator<std::string> edge_iter(fileEdges);
        // Ignore first line
        ++edge_iter;
        while (!fileEdges.eof())
        {
            std::vector<std::string> edgeData = split(*edge_iter, ",");
            //undirected graph, so both orders of pairs get same bool
            int first = std::stoi(edgeData[0]);
            int second = std::stoi(edgeData[1]);
            adjacency_matrix[first][second] = 1;
            adjacency_matrix[second][first] = 1;
            ++edge_iter;
        }
    }
    // copy adjacency matrix to steady state / markov matrix
    amatrix.resize(adjacency_matrix.size(), std::vector<double>(adjacency_matrix[0].size()));
    for (size_t i = 0; i < adjacency_matrix.size(); i++)
    {
        for (size_t j = 0; j < adjacency_matrix.size(); j++)
        {
            if (adjacency_matrix[i][j])
            {
                amatrix[i][j] = 1;
            }
            else
            {
                amatrix[i][j] = 0;
            }
        }
    }
}


bool Graph::is_connected(int node1, int node2){
  	//no need to check both ways since graph is undirected
	return adjacency_matrix[node1][node2];
}

std::vector<int> Graph::BFS(int start){
  //initialize visited vector to false
  std::vector<bool> visited(numVertices + 1, 0);
  //BFS, so use a queue
  std::queue<int> q;
  //traversal path results
  std::vector<int> traversal;
  //set start as visited
  visited[start] = 1;
  q.push(start);

  while(!q.empty()){
    int s = q.front();
    q.pop();
    //add the front of the queue to the path
    traversal.push_back(s);
    //iterate through number of vertices
    for(int it = 0; it < numVertices + 1; it++){
     //only push to queue if value in adjacency matrix is true   
     if(!visited[it] && adjacency_matrix[s][it]){
        visited[it] = 1;
        q.push(it);
      }
    }
  }
  return traversal;
}

void Graph::test()
{
    std::vector<int> traversal = BFS(1);
    for(unsigned i = 0; i < traversal.size(); i++){
      std::cout << traversal[i] << " ";
    }
    std::cout << std::endl;

    printAdjacencyMatrix(numVertices+1);
}

// Based off of https://stackoverflow.com/questions/5607589/right-way-to-split-an-stdstring-into-a-vectorstring
std::vector<std::string> Graph::split(std::string str, std::string token)
{
    std::vector<std::string> result;

    while (str.size())
    {
        int index = str.find(token);
        if (index != -1)
        {
            result.push_back(str.substr(0, index));
            str = str.substr(index + token.size());
            if (str.size() == 0)
            {
                result.push_back(str);
            }
        }
        else
        {
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

void Graph::printAdjacencyMatrix(int size)
{
    std::cout << std::endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            std::cout << adjacency_matrix[i][j] << "    ";
        }
        std::cout << std::endl;
    }
}


int Graph::get_numVertices() {
    return numVertices;
}

std::map<int, int> Graph::get_data() {
    return data;
}
