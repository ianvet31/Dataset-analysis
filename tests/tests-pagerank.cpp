#include "../cs225/catch/catch.hpp"
#include "../pagerank.h"
#include "iostream"

TEST_CASE("validSquareMatrix", "[weight=5][timeout=8000]")
{
    Graph g = Graph("users_test_data.csv", "edges_test_data.csv");
    Pagerank p = Pagerank();
    p.setupPageRank(g);
    bool isValid = true;
    size_t size = g.amatrix.size();
    for (size_t i = 0; i < g.amatrix.size(); i++)
    {
        if (g.amatrix[i].size() != size)
        {
            isValid = false;
        }
    }
    REQUIRE(isValid);
}

TEST_CASE("validMarkovMatrix", "[weight=5][timeout=8000]")
{
    Graph g = Graph("users_test_data.csv", "edges_test_data.csv");
    Pagerank p = Pagerank();
    p.setupPageRank(g);
    bool isValid = true;
    for (size_t i = 0; i < g.amatrix.size(); i++)
    {
        double sum = 0;
        for (size_t j = 0; j < g.amatrix.size(); j++)
        {
            sum += g.amatrix[j][i];
        }
        REQUIRE(sum < 1.0 + 1E-15);
        REQUIRE(sum > 1.0 - 1E-15);
    }
}

TEST_CASE("unitVectorGeneration", "[weight=5][timeout=8000]")
{
    Graph g = Graph("users_test_data.csv", "edges_test_data.csv");
    Pagerank p = Pagerank();
    p.randomunitvectorgenerator(g);
    bool isValid = true;
    vector<double> vec = p.getRandomUnitVector();
    double sum = 0;
    for (size_t j = 0; j < vec.size(); j++)
    {
        sum += vec[j];
    }
    REQUIRE(sum < 1.0 + 1E-15);
    REQUIRE(sum > 1.0 - 1E-15);
}

TEST_CASE("matrixMultiplication basic", "[weight=5][timeout=8000]")
{
    vector<vector<double>> v1 = {{0.3, 0.1},
                                 {0.7, 0.9}};
    vector<double> v2 = {0.23, 0.77};
    Pagerank p = Pagerank();
    vector<double> calculatedResult = p.matrixmultiplication(v1, v2);
    vector<double> sol = {0.23 * 0.3 + 0.1 * 0.77, 0.23 * 0.7 + 0.77 * 0.9};
    REQUIRE(calculatedResult == sol);
}

TEST_CASE("matrixMultiplication advanced", "[weight=5][timeout=8000]")
{
    vector<vector<double>> v1 = {{0.4, 0.1, 0, 0.25},
                                 {0.2, 0, 0.5, 0.25},
                                 {0.2, 0.9, 0.5, 0.25},
                                 {0.2, 0, 0, 0.25}};
    vector<double> v2 = {0.11, 0.5, 0.24, 0.15};
    Pagerank p = Pagerank();
    vector<double> calculatedResult = p.matrixmultiplication(v1, v2);
    vector<double> sol = {0.4 * 0.11 + 0.1 * 0.5 + 0.25 * 0.15, 0.2 * 0.11 + 0.24 * 0.5 + 0.25 * 0.15, 0.2 * 0.11 + 0.9 * 0.5 + 0.5 * 0.24 + 0.25 * 0.15, 0.11 * 0.2 + 0.15 * 0.25};
    REQUIRE(calculatedResult == sol);
}

TEST_CASE("finalPagerankSum", "[weight=5][timeout=8000]")
{
    double sum = 0;
    Graph g = Graph("users_test_data.csv", "edges_test_data.csv");
    Pagerank p = Pagerank();
    p.powerPageRank(g, 100);
    vector<double> calculatedPageRankWeights = p.getRandomUnitVector();
    for (size_t j = 0; j < calculatedPageRankWeights.size(); j++)
    {
        sum += calculatedPageRankWeights[j];
    }
    REQUIRE(sum < 1.0 + 1E-5);
    REQUIRE(sum > 1.0 - 1E-5);
}