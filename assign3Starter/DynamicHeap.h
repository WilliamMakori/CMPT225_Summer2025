// Student Name: 
// CMPT 225 Assignment #3
//Created by Jocelyn Minns, 
//Based on content from Chris Schmidt, please do not make available online
#ifndef DYNAMICHEAP_H
#define DYNAMICHEAP_H
#include <iostream>
//DO NOT EDIT THE FUNCTIONS SPECIFIED HERE
//You may add additional private helper functions as needed 
//SEE MORE DOCUMENTATION IN DynamicHeap.cpp

//Stores max-heap using an array whose capacity is reduced or increased based on the number of values
class DynamicHeap {

public: 
    DynamicHeap();
    DynamicHeap(const DynamicHeap& other);
    ~DynamicHeap();
    DynamicHeap& operator=(const DynamicHeap& other);
    void insert(int key);
    int removeMax();
    int getSize() const;
    void printHeap(std::ostream& out) const;

private:
    int* heap = nullptr;
    int capacity=7;
    void increaseCapacity();
    void decreaseCapacity();
    
};
#endif
