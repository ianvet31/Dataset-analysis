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
        random = rand() % 10000 + 1;
        randomunitvector[i] = random;
        total += random;
    }
    for (auto i = 0; i < size; i++)
    {
        randomunitvector[i] /= total;
    }
}

void Pagerank::print1dvector(vector<double> vec)
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << "    ";
    }
    cout << endl << endl;
}

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

void Pagerank::powerPageRank(Graph &graph, int iterations)
{
    setupPageRank(graph);
    // printAmatrix(graph);
    randomunitvectorgenerator(graph);

    damping(graph, 0.85);
    for (int i = 0; i < iterations; i++) {
        randomunitvector = matrixmultiplication(graph.amatrix, randomunitvector);
    }
    leaderboardSortPrint(randomunitvector);
}

void Pagerank::printAmatrix(Graph &graph) {
    size_t size = graph.amatrix.size();
    cout << "[";
    for (size_t j = 0; j < size; j++)
    {
        cout << "[";
        for (size_t k = 0; k < size; k++)
        {
            cout << graph.amatrix[j][k] << (k != size - 1 ? ", " : "");
        }
        cout << "]" << (j != size - 1 ? ", " : "") << (j != size - 1 ? "\n" : "");
    }
    cout << "]" << endl;
}

void Pagerank::leaderboardSortPrint(vector<double> vec) {
    vector<vector<double>> leaderboard;
    int s = vec.size();
    leaderboard.resize(s, vector<double>(2));
    for (int i = 0; i < s; i++) {
            leaderboard[i][0] = i;
            leaderboard[i][1] = randomunitvector[i];
    }

    sort(leaderboard.begin(), leaderboard.end(), sortHelper);

    cout << "Rank  |   User  |   Pagerank Weight" << endl;
    for (size_t i = 0; i < leaderboard.size(); i++) {
        cout << (i+1) << ")        " << leaderboard[i][0] << "       " << leaderboard[i][1] << endl;
    }
}

bool Pagerank::sortHelper(const vector<double>& v1, const vector<double>& v2) {
    return v1[1] > v2[1];
}

vector<double> Pagerank::getRandomUnitVector() {
    return randomunitvector;
}