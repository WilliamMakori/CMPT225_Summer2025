// Name: 
// CMPT 225 Assignment #5
// Created by Jocelyn Minns, based on content from Chris Schmidt
// please do not make available online
#include "Graph.h"
#include <string>
#include <queue>
#include <iostream> 
using std::string, std::cout, std::endl;
using std::queue;


//Implemented for you: do not edit
//Constructor to initialize the Graph
Graph::Graph() {
    buildTestGraphA();
}

//Implemented for you: do not edit
Graph::~Graph() {
    clearGraph();
}

//IMPLEMENT
//Find and print the shortest path from the source to all other nodes
//Print no path for any node that is unreachable
//If the source node does not exist, print a message that it wasn't found
//Use Dijkstra's algorithm
//The heap (priority queue) has been implemented for you

void Graph::findAllShortestPathsFrom(string source) {
    // comment out once implemented
    
    // cout << "findAllShortestPathsFrom is not implemented" << endl;
    
    if(vertexArray == nullptr || vertexCount == 0)
    {
        cout << "Graph is empty" << endl;
        return;
    }
    
    // find the source if it exists, first declare the start vertex and then iterate through the vertexArray to check for the source
    Vertex* start = nullptr;
    
    //find the index
    int startIndex = -1;
    for(int i = 0; i < vertexCount; i++){
        if(vertexArray[i]->name == source){
            startIndex = i;
            break; // to avoid unnecesary loop iterations
        }
    }
    if(startIndex == -1){
        cout << source << " vertex has not been found." << endl;
        return;
    }
    // we've found it
    // initialize the start
    start = vertexArray[startIndex];
    
    // initialize distances and prev
    clearLabelsPrevs(INF);
    start->label = 0; // distance from start to start
    start->prev = nullptr; // we start here no previous vertices
    
    // fill the heap with all the vertices
    // visualized for simplicity
    
    fillHeap();
    
    // Djkstra's
    
    while(!heapEmpty()){
        Vertex* u = removeHeapMin();
        if(!u)
            break;
        if(u->label == INF)
            break;
        
        for(AdjListNode* e = u->neighbors; e!=nullptr; e = e->next){
            Vertex* w = e->v;
            int wgt = e->weight;
            
            if(u->label != INF && u->label + wgt < w->label){
                w->label = u->label + wgt;
                w->prev = u;
                bubbleUp(w);
            }
        }
        
        
    }
    
    // clean up
    
    deleteHeap();
    
    // Loop through the vertex list and print out the paths
    for(int i = 0; i < vertexCount; ++i){
        
        Vertex* v = vertexArray[i];
        // minor change from the pdf
        
        // if the label is still INF
        if(v->label == INF){
            cout << "No path from " << source << " to " << v->name << endl;
        }
        
        // otherwise print the path from the source to that vertex
        else{
            printPath(v);
            cout << endl;
        }
    }
    
    
}
//IMPLEMENT
//Find and print a path to all other nodes from the source
//Uses simple BFS, DOES NOT CONSIDER THE WEIGHTS OF EDGES
//Print a message saying there is no path for any node that is unreachable
//If the source node does not exist, print a message that it wasn't found
//Use the c++ stl queue
void Graph::findPathsWithBFSFrom(string source) {
    // commment out this line after implementation
    
    // cout << "findPathsWithBFSFrom is not implemented" << endl;, dunzo
    
    Vertex* start = nullptr;
    if(vertexArray == nullptr || vertexCount == 0)
    {
        cout << " Graph is empty" << endl;
        return; // There's nothing in the graph
    }
    else{
        // search for the vertex with the source name
        // vertexCount - number of vertices in the graph
        // if you find it, return the index, and then set it as the start position
        
        int startIndex = -1;
        
        for(int i = 0; i < vertexCount; ++i){
            if(vertexArray[i]->name == source){
                startIndex = i;
                break;
            }
        }
        
        if(startIndex == -1){
            cout << source << " vertex not found" << endl;
            return;
        }
        // we've found it
        // set the starting point appropriately
        
        
        start = vertexArray[startIndex];
        
        // let's continue
        // we now have the starting vertex
        // set all the labels to INF, unvisited
        clearLabelsPrevs(INF);
        
        start->label = 0;
        start->prev = nullptr;
        
        // usig the queue from the C++ std lib
        queue<Vertex *> q;
        
        // push the start vertex on to the queue
        q.push(start);
        
        //BFS
        while(!q.empty()){
            // peek and then pop
            
            Vertex* u = q.front();
            q.pop();
            
            // traverse through the adjacency list, which is a linkedlist so until the pointer is null
            
            for(AdjListNode* e = u->neighbors; e!=nullptr; e = e->next){
                Vertex* w = e->v;
                // if the vertex is unvisited, change the label to indicate that we've visited it
                
                if(w->label == INF){
                    w->label = u->label + 1;
                    w->prev = u;
                    q.push(w);
                }
            }
        }
        
        // Loop through the vertex list
        for(int i = 0; i < vertexCount; ++i){
            
            Vertex* v = vertexArray[i];
            // minor change from the pdf
            
            // if the label is still INF
            if(v->label == INF){
                cout << "No path from " << source << " to " << v->name << endl;
            }
            
            // otherwise print the path from the source to that vertex
            else{
                printPath(v);
                cout << endl;
            }
        }
        
        
        
    }
}



void Graph::clearLabelsPrevs(int labelVal) {
    if (vertexArray) {
        for (int i=0; i<vertexCount; i++) {
            vertexArray[i]->label=labelVal;
            vertexArray[i]->prev=nullptr;
        }
    }
}


void Graph::printPath(Vertex* v) {
    if (v) {
        if (v->label == INF) {
            cout << "NONE";
            return;
        }

        printPath(v->prev);
        cout << " > " << v->name <<"(" << v->label <<")";
    }
}

//Implemented for you: do not edit
//Initializes the heap with all vertices
//The heap uses the label for it's sorting
//The vertex labels must all be set before calling this
void Graph::fillHeap() {
    vHeap = new Vertex* [vertexCount+1];
    vHeapSize = 0;
    for (int i=0; i<vertexCount; i++) {
        vHeapSize++;
        vHeap[vHeapSize]=vertexArray[i];
        vertexArray[i]->heapIndex=vHeapSize;
        bubbleUp(vertexArray[i]);
    }
}


//Implemented for you: do not edit
//deletes the heap
void Graph::deleteHeap() {
    if (!vHeap) {
        return;
    }
    delete[] vHeap;
    vHeap=nullptr;
    vHeapSize=-1;
}

//Implemented for you: do not edit
//Removes and returns the minimum (label value) Vertex from the heap
Graph::Vertex* Graph::removeHeapMin() {
    if (vHeapSize==0) {
        return nullptr;
    }

    Vertex* removed = vHeap[1];
    removed->heapIndex=-1;

    if (vHeapSize>1) {
        vHeap[1] = vHeap[vHeapSize];
        vHeap[1]->heapIndex = 1;
    }
    vHeapSize--;

    int curr = 1;
    bool done = false;
    while (curr*2<=vHeapSize && !done){
        int swapIndex=curr;
        done=true;
        if (vHeap[curr*2]->label < vHeap[curr]->label) {
            swapIndex=curr*2;
            done=false;
        }

        if (curr*2+1 <= vHeapSize && vHeap[curr*2+1]->label < vHeap[swapIndex]->label) {
            swapIndex=curr*2+1;
            done=false;
        }
        if (!done) {
            Vertex* temp = vHeap[curr];
            vHeap[curr] = vHeap[swapIndex];
            vHeap[curr]->heapIndex=curr;
            vHeap[swapIndex]=temp;
            vHeap[swapIndex]->heapIndex=swapIndex;
            curr=swapIndex;
        }
    }
    return removed;
}

//Implemented for you: do not edit
//Prints the heap
//Use for debugging your algorithms
void Graph::printHeap() {
    if (vHeap) {
        cout << "Heap Contents" << endl;
        for (int i=1; i<=vHeapSize; i++) {
            int w = vHeap[i]->label;
            cout << i  <<":"<<vHeap[i]->name << ": ";
            if (w==INF) {
                cout << "Infinity" << endl;
            } else {
                cout << w << endl;
            }
        }
    }
}

//Implemented for you: do not edit
//checks if the heap is empty
//the result is only meaningful while the heap exists during Dijkstra's algorithm
bool Graph::heapEmpty() {
    return vHeapSize == 0;
}

//Implemented for you: do not edit
//Will "bubble" the given vertex up the heap if needed
//This should be called after the label for the vertex has 
//been decreased during Dijkstra's algorithm

void Graph::bubbleUp(Vertex* v) {
    int i = v->heapIndex;

    while (i>1 && v->label < vHeap[i/2]->label) {
        
        vHeap[i]=vHeap[i/2];
        
        vHeap[i]->heapIndex=i;
        
        i=i/2;
    }

    vHeap[i]=v;
    v->heapIndex=i;
}


//Implemented for you: do not edit
//deletes all dynamically allocated memory
void Graph::clearGraph() {
    // check if the vertexArray is empty
    // if it's not
    
    if (vertexArray) {
        
        for (int i=0; i<vertexCount; i++) {
            
            AdjListNode* curr=vertexArray[i]->neighbors;
            
            AdjListNode* prev=curr;
            
            while(curr) {
                
                curr=curr->next;
                
                delete prev;
                
                prev=curr;
                
            }
            
            delete vertexArray[i];
            
        }
        
        delete[] vertexArray;
        
        vertexArray=nullptr;
    }
}


// this makes sense, we print the name of the vertex name and then we print the names of the neighbours by going through the linkedlist

//Implemented for you: do not edit
//Prints all nodes with their adjacency lists

void Graph::printGraph() const {
    
    // check if the vertexArray points to a null object
    
    if (!vertexArray) {
        cout << "Graph is empty" << endl;
        
    }
    
    else {
        // go through all the vertices using a for loop
        
        for (int i=0; i<vertexCount; i++) {
            B
            // print the name and then print the edges
            
            cout << vertexArray[i]->name << "  edges (vertex/weight):";
            
            AdjListNode* curr = vertexArray[i]->neighbors;
            
            while (curr) {
                
                cout << curr->v->name << "/" << curr->weight << "  ";
                
                curr=curr->next;
                
            }
            
            cout << endl;
            
        }
        
    }
    
    cout << endl;
    return;
}



// this portion makes complete sense now
//Implemented for you: do not edit
//builds graph A from the assignment instructions
//Should be done better, but this works for now.  :)
void Graph::buildTestGraphA() {
    //remove all current vertices and edges
    clearGraph();
    // number of vertices in the graph
    vertexCount=5;
    
    // define the vertexArray as a dynamic array with a size of 5
    vertexArray=new Vertex*[vertexCount];
    
    // here we use an arbitrary value 5, and then add five new vertices to the array
    
    vertexArray[0]=new Vertex{"A"};
    vertexArray[1]=new Vertex{"B"};
    vertexArray[2]=new Vertex{"C"};
    vertexArray[3]=new Vertex{"D"};
    vertexArray[4]=new Vertex{"E"};
    
    
    // ?? each vertex entry in the dynamic array has a vertex object in it
    // we set the name
    // and then we set the neighbours
    
    vertexArray[0]->neighbors=new AdjListNode{vertexArray[1],10, new AdjListNode{vertexArray[2], 3}};
    vertexArray[1]->neighbors=new AdjListNode{vertexArray[2],1, new AdjListNode{vertexArray[3],2}};
    vertexArray[2]->neighbors=new AdjListNode{vertexArray[1],4, new AdjListNode{vertexArray[3],8, new AdjListNode{vertexArray[4],2}}};
    vertexArray[3]->neighbors=new AdjListNode{vertexArray[4],7};
    vertexArray[4]->neighbors=new AdjListNode{vertexArray[3],9};
}

// this part now makes complete sense

//Implemented for you: do not edit
//builds graph B from the assignment instructions
//Should be done better, but this works for now.  :)
void Graph::buildTestGraphB() {
    clearGraph();
    vertexCount=12;
    vertexArray=new Vertex*[vertexCount];

    vertexArray[0]=new Vertex{"A"};
    vertexArray[1]=new Vertex{"B"};
    vertexArray[2]=new Vertex{"C"};
    vertexArray[3]=new Vertex{"D"};
    vertexArray[4]=new Vertex{"E"};
    vertexArray[5]=new Vertex{"F"};
    vertexArray[6]=new Vertex{"G"};
    vertexArray[7]=new Vertex{"H"};
    vertexArray[8]=new Vertex{"I"};
    vertexArray[9]=new Vertex{"J"};
    vertexArray[10]=new Vertex{"K"};
    vertexArray[11]=new Vertex{"L"};

    vertexArray[0]->neighbors=new AdjListNode{vertexArray[1],1};
    vertexArray[1]->neighbors=new AdjListNode{vertexArray[0],1, new AdjListNode{vertexArray[2], 3}};
    vertexArray[2]->neighbors=new AdjListNode{vertexArray[1],3, new AdjListNode{vertexArray[3],2, new AdjListNode{vertexArray[9],30}}};
    vertexArray[3]->neighbors=new AdjListNode{vertexArray[2],2, new AdjListNode{vertexArray[4],1, new AdjListNode{vertexArray[8],2}}};
    vertexArray[4]->neighbors=new AdjListNode{vertexArray[5],1, new AdjListNode{vertexArray[7],10, new AdjListNode{vertexArray[3],1}}};
    vertexArray[5]->neighbors=new AdjListNode{vertexArray[6],3, new AdjListNode{vertexArray[4], 1}};
    vertexArray[6]->neighbors=new AdjListNode{vertexArray[5],3, new AdjListNode{vertexArray[7], 5}};
    vertexArray[7]->neighbors=new AdjListNode{vertexArray[4],10, new AdjListNode{vertexArray[6],5, new AdjListNode{vertexArray[8],2}}};
    vertexArray[8]->neighbors=new AdjListNode{vertexArray[9],5, new AdjListNode{vertexArray[3],2, new AdjListNode{vertexArray[7],2}}};    
    vertexArray[9]->neighbors=new AdjListNode{vertexArray[10],1, new AdjListNode{vertexArray[8],5, new AdjListNode{vertexArray[2],30}}};
    vertexArray[10]->neighbors=new AdjListNode{vertexArray[9],1};
}
