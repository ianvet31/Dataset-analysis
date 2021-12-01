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

Graph::Graph(std::string datafile, std::string edgefile) {
    std::ifstream fileData(datafile);
    std::ifstream fileEdges(edgefile);

    if (fileData.is_open()) {
        std::istream_iterator<std::string> data_iter(fileData);
        // Ignore first line
        ++data_iter;
        while (!fileData.eof()) {
            // views,mature,life_time,created_at,updated_at,numeric_id,dead_account,language,affiliate
            // 0     1      2         3          4          5          6            7        8
            std::vector<std::string> lineData = split(*data_iter, ",");
            // id, views
            data.insert({std::stoi(lineData[5]), std::stoi(lineData[0])});
            ++data_iter;
        }
    }
}

void Graph::test() {
    std::cout << data[1] << std::endl;
}

// Based off of https://stackoverflow.com/questions/5607589/right-way-to-split-an-stdstring-into-a-vectorstring
std::vector<std::string> Graph::split(std::string str, std::string token){
    std::vector<std::string> result;

    while(str.size()){
        int index = str.find(token);
        if(index != -1){
            result.push_back(str.substr(0, index));
            str = str.substr(index + token.size());
            if(str.size() == 0) {
                result.push_back(str);
            }
        } else {
            result.push_back(str);
            str = "";
        }
    }
    return result;
}
