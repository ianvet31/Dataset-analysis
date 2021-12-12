/**
 * @file pagerank.cpp
 * Implementation of the pagerank algorithm based on https://en.wikipedia.org/wiki/PageRank.
 */

#include "pagerank.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <vector>

#include <cmath>
#include <ctime>
#include <stdio.h>  /* printf, scanf, puts, NULL */
#include <stdlib.h> /* srand, rand */
#include <sys/time.h>

using namespace std;

Pagerank::Pagerank()
{
}

// setupPageRank(Graph &graph) sets up markov matrix based on adgacency matrix of graph provided
void Pagerank::setupPageRank(Graph &graph)
{
    size_t size = graph.amatrix.size();
    for (size_t i = 0; i < size; i++)
    {
        int count = 0;
        for (size_t j = 0; j < size; j++)
        {
            if (graph.amatrix[j][i])
            {
                count++;
            }
        }
        if (count == 0)
        {
            for (size_t j = 0; j < size; j++)
            {
                graph.amatrix[j][i] = double(1) / double(size);
            }
        }
        else
        {
            for (size_t j = 0; j < size; j++)
            {
                graph.amatrix[j][i] = double(graph.amatrix[j][i]) / double(count);
            }
        }
    }
    return;
}

// randomunitvectorgenerator(Graph &graph) generates random unit vector the same size of the columns in the markov matrix (amatrix)
void Pagerank::randomunitvectorgenerator(Graph &graph)
{
    int size = graph.amatrix.size();
    randomunitvector.resize(size);
    struct timeval start;
    gettimeofday(&start, NULL);
    srand(start.tv_usec * start.tv_sec);
    int random = 0;
    double total = 0;
    for (auto i = 0; i < size; i++)
    {
        random = rand() % size + 1;
        randomunitvector[i] = random;
        total += random;
    }
    for (auto i = 0; i < size; i++)
    {
        randomunitvector[i] /= total;
    }
}

// print1dvector(vector<double> vec) prints out a 1 dimentional vector<double> in a readable format
void Pagerank::print1dvector(vector<double> vec)
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << "    ";
    }
    cout << endl
         << endl;
}

// damping(Graph &graph, double damping) adjusts the markov matrix based on the damping number for provided graph
void Pagerank::damping(Graph &graph, double damping)
{
    size_t size = graph.amatrix.size();
    for (size_t j = 0; j < size; j++)
    {
        for (size_t k = 0; k < size; k++)
        {
            graph.amatrix[j][k] = damping * graph.amatrix[j][k] + (1 - damping) / size;
        }
    }
}

// matrixmultiplication(vector<vector<double>> d2v, vector<double> d1v) multiplies a 2 dimentional matrix by a 1 dimentional matrix returning the resulting 1 dimentional matrix
vector<double> Pagerank::matrixmultiplication(vector<vector<double>> d2v, vector<double> d1v)
{
    vector<double> result;
    for (size_t i = 0; i < result.size(); i++)
    {
        result[i] = 0;
    }
    for (size_t i = 0; i < d2v.size(); i++)
    {
        double total = 0;
        for (size_t j = 0; j < d2v[0].size(); j++)
        {
            total += d2v[i][j] * d1v[j];
        }
        result.push_back(total);
    }
    return result;
}

/**
 * Complete implementation of the power iteration pagerank algorithm that uses damping to rank the users on twitch.
 *      - Step 1) Setup markov matrix based on adgacency matrix
 *      - Step 2) Generate random unit vector the same size as the rows in the markov matrix
 *      - Step 3) Use damping helper to damp markov matrix based on the damping factor
 *      - Step 4) Iterate through and multiply the matrix by the random unit vector multiple times until the pageranks weights converge to an acceptable error margin
 *      - Step 5) Sort users by pagerank weight and print in reasonable and readable format
 */
void Pagerank::powerPageRank(Graph &graph, int iterations)
{
    printAmatrix(graph);
    setupPageRank(graph);
    randomunitvectorgenerator(graph);

    damping(graph, 0.85);
    for (int i = 0; i < iterations; i++)
    {
        cout << "started step " << i+1 << " out of " << iterations << " iterations " << endl;
        randomunitvector = matrixmultiplication(graph.amatrix, randomunitvector);
    }
    leaderboardSortPrint(randomunitvector);
}

// printAmatrix(Graph &graph) exports the amatrix for provided graph in its given state
void Pagerank::printAmatrix(Graph &graph)
{
    ofstream myfile;
    myfile.open("currentamatrix.txt", ofstream::out | ofstream::trunc);
    if (myfile.is_open())
    {

        size_t size = graph.amatrix.size();
        myfile << "[";
        for (size_t j = 0; j < size; j++)
        {
            myfile << "[";
            for (size_t k = 0; k < size; k++)
            {
                myfile << graph.amatrix[j][k] << (k != size - 1 ? ", " : "");
            }
            myfile << "]" << (j != size - 1 ? ", " : "") << (j != size - 1 ? "\n" : "");
        }
        myfile << "]" << endl;
    }
}

// leaderboardSortPrint(vector<double> vec) sorts vector<double> into a leaderboard format for the pagerank output with ranks and pagerank weight and prints top 10
void Pagerank::leaderboardSortPrint(vector<double> vec)
{
    ofstream myfile;
    myfile.open("pagerank_leaderboard.txt", ofstream::out | ofstream::trunc);
    if (myfile.is_open())
    {
        vector<vector<double>> leaderboard;
        int s = vec.size();
        leaderboard.resize(s, vector<double>(2));
        for (int i = 0; i < s; i++)
        {
            leaderboard[i][0] = i;
            leaderboard[i][1] = randomunitvector[i];
        }

        sort(leaderboard.begin(), leaderboard.end(), sortHelper);

        myfile << "Rank  |   User  |   Pagerank Weight" << endl;
        for (size_t i = 0; i < leaderboard.size(); i++)
        {
            myfile << (i + 1) << ")        " << leaderboard[i][0] << "       " << leaderboard[i][1] << endl;
        }
        myfile.close();
    }
}

// sortHelper(const vector<double>& v1, const vector<double>& v2) used to help sort the leaderboard vector into a readable and useful format
bool Pagerank::sortHelper(const vector<double> &v1, const vector<double> &v2)
{
    return v1[1] > v2[1];
}

// Pagerank::getRandomUnitVector() getter for randomunitvector so it can be accessed publicly
vector<double> Pagerank::getRandomUnitVector()
{
    return randomunitvector;
}