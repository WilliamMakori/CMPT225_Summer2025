// Name: 
// CMPT 225 Assignment #5
// Created by Jocelyn Minns, based on content from Chris Schmidt
// please do not make available online

#include "Graph.h"
#include <iostream>
using std::string, std::cout, std::endl;

int main() {
    cout << "TESTING GRAPH A" << endl;
    Graph* g = new Graph();
    g->printGraph();

    cout << "\n\nFinding Paths From Vertex A with BFS" << endl;
    g->findPathsWithBFSFrom("A");

    cout << "\n\nFinding Shortest Paths From Vertex A with Dijkstra's" << endl;
    g->findAllShortestPathsFrom("A");


    g->buildTestGraphB();
    cout << "\n\nTESTING GRAPH B" << endl;
    g->printGraph();

    cout << "\n\nFinding Paths From Vertex A with BFS" << endl;
    g->findPathsWithBFSFrom("A");

    cout << "\n\nFinding Shortest Paths From Vertex A with Dijkstra's" << endl;
    g->findAllShortestPathsFrom("A");

    return 0;
}
