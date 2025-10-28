// Name:
// CMPT 225 Assignment #5
// Created by Jocelyn Minns, based on content from Chris Schmidt
// please do not make available online
#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <climits>
using std::string;

//DO NOT EDIT THE FUNCTIONS SPECIFIED HERE
//You may add additional private helper functions as needed

//SEE MORE DOCUMENTATION IN Graph.cpp and the assignment instructions

//Graph using Adjacency List 
class Graph {

public: 
    Graph();
    ~Graph();
  
    void findPathsWithBFSFrom(string source);
    void findAllShortestPathsFrom(string source);
    
    void printGraph() const;

    void buildTestGraphA();
    void buildTestGraphB();

private:
    struct Vertex; //AdjListNode and Vertex use each other, so this is needed

    struct AdjListNode {
        // here we have a pointer to the vertex,
        
        Vertex* v;  //the neighbor
        
        int weight; //weight of the edge
        // when 
        AdjListNode* next=nullptr; //next node in the adjacency list
    };

    struct Vertex {
        string name;    //The name of the node
        AdjListNode* neighbors = nullptr;   //adjacency list of neighbors

        int heapIndex=-1;   //Vertex knows where it is in the heap for quick access

        Vertex* prev=nullptr;   //previous node in the path 
        int label=-1;   //label
    };

    //Vertex array, only needed when we need to iterate over all vertices
    Vertex* * vertexArray=nullptr;
    int vertexCount;

    //for the heap used in Dijkstra's
    int vHeapSize=-1;
    Vertex* * vHeap=nullptr;

    //Used to mark vertices that have no discoverred path yet
    const int INF = INT_MAX;
    
    //Used to label vertexes as needed in algoirthms
    const int UNVISITED = 0;
    const int VISITED = 1;
    
    
    void fillHeap();
    void deleteHeap();
    Vertex* removeHeapMin();
    void bubbleUp(Vertex* v);
    void printHeap();

    bool heapEmpty();


    void clearGraph();


    void clearLabelsPrevs(int labelVal);
    void printPath(Vertex* v);

};
#endif
