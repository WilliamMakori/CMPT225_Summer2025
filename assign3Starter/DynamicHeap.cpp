// Student Name: Makori William Dennis Chacha
// CMPT 225 Assignment #3
//Created by Jocelyn Minns, 
//Based on content from Chris Schmidt, please do not make available online
#include "DynamicHeap.h"
#include <iostream>
#include <iomanip>
#include <string>
using std::cout;
using std::cin;
using std::endl;

//A max-heap stored as an array which will be reallocated with increased or decreased size as appropriate
//The initial capacity is 7 data values with index 0 storing how many values are actually in the heap

//IMPLEMENT
//set up the heap array
DynamicHeap::DynamicHeap() {
    heap = new int[capacity];
    heap[0] = 0; // Size is 0, no elements in the array.
    
}

//IMPLEMENT
DynamicHeap::~DynamicHeap() {
    delete []heap;
}

//IMPLEMENT
DynamicHeap::DynamicHeap(const DynamicHeap& other){
    // copy constructor, perform a deep copy
    this->capacity = other.capacity;
    this->heap = new int[capacity];
    
    for(int i = 0; i <= other.heap[0]; i++){
        this->heap[i] = other.heap[i];
    }
        
}

//IMPLEMENT
//The current heap should have the same values and structure as the parameter
DynamicHeap& DynamicHeap::operator=(const DynamicHeap& other) {
    
    if(this == &other)
        return *this;
    
    delete[] heap; // free up the memory to avoid memory leak
    
    this->capacity = other.capacity;
    this->heap = new int[capacity];
    
    // deep copy for all the values
    for (int i = 0; i <= other.heap[0]; i++){
        this->heap[i] = other.heap[i];
    }
    
    return *this;
    
}


//return the size NOT the capacity
int DynamicHeap::getSize() const {
    return heap[0];
}

//IMPLEMENT
//Follow the insert algorithm from slides/text
//Call increaseCapacity if there isn't room for the new element
void DynamicHeap::insert(int key){
    // steps
    // check if the capacity is the same as the size
    // increase the size at the end
    // if the size is the same as the capacity, call increasecapacity to double the capacity of the array
    if(this->heap[0] == this->capacity){
        increaseCapacity();
    }
    // increase the size of the array
    heap[0]++;
    // add the new element to the end of the array
    int index = this->heap[0];
    heap[index] = key;
    // percolate up
    
    while(index > 1){
        int parent = index / 2;
        if(this->heap[index] > heap[parent]){
            std::swap(heap[index], heap[parent]);
            index = parent;
        }
        else{
            break;
        }
    }
}

//IMPLEMENT
//Remove and return the max value
//Return -1 if the heap is empty
//Follow the insert algorithm from slides/text
//Call decreaseCapacity if the size is less than a quarter of the capacity when done AND greater than 7
int DynamicHeap::removeMax() {
    
    // if heap is empty -1 is returned
    
    int max = -1;
    
    // heap isn't empty
    if (heap[0] != 0){
        // reassign the value of max
        
        max = heap[1];
        // reassign the root value with the last element in the array
        
        heap[1] = heap[heap[0]];
        // decrease the size and then percolate down
        
        heap[0]--;
        
        int index = 1;
        
        while (2 * index <= heap[0]) {
            
            int left = 2 * index;
            int right = 2 * index + 1;
            int largest = index;

            if (left <= heap[0] && heap[left] > heap[largest]) {
                largest = left;
            }
            if (right <= heap[0] && heap[right] > heap[largest]) {
                largest = right;
            }

            if (largest == index) {
                break; // Heap property is restored
            }

            std::swap(heap[index], heap[largest]);
            index = largest;
            
        }

        // Decrease capacity if too much unused space
        if (heap[0] <= capacity / 4 && capacity > 7) {
            decreaseCapacity();
        }
    }
    
    return max;
}

//IMPLEMENT
//Make room for a new level of nodes by allocating a new array and copying the appropriate values into it
//Double the capacity and add 1, 7 -> 15 -> 31 -> 63...
void DynamicHeap::increaseCapacity() {
    // this function only gets called when the size is equal to the capacity.
    
    // increase the capacity first
    this->capacity = this->capacity * 2;
    this->capacity += 1;
    
    //create a new array and copy over the values
    int* newHeap = new int[capacity]; // new array with the new capacity value
    
    // copy the values over from the old array
    
    for(int i = 0; i <= this->heap[0] ; i++){
        newHeap[i] = this->heap[i];
    }
    
    delete []heap;
    
    heap = newHeap;
    
}

//IMPLEMENT
//Reduce capacity by allocating a new array and copying the appropriate values into it
//Divide the capacity by 2 (relying on integer division)
void DynamicHeap::decreaseCapacity() {
    
    // half the capacity
    this->capacity = capacity/2;
    // new array with the new capacity
    int* newHeap = new int[capacity];
    // copy elements over
    for(int i = 0; i <= heap[0]; i++){
        newHeap[i] = heap[i];
    }
    // free up memory
    delete[] heap;
    // reassign the memory slot
    
    heap = newHeap;
    
}

//Implemented for you
//Prints out the heap's current values
void DynamicHeap::printHeap(std::ostream& out) const {
    out << "Capacity:" << capacity << " Size:" << heap[0] << endl;

    std::string filler = "   ";

    int i = 1;
    int gap = 1;
    while (2 * i <= heap[0]) {
        i *= 2;
        gap = 2 * gap + 1;
    }
    for (int j = 0; j < gap / 2; j++) {
        out << filler;
    }
    int newline = 1;
    for (int i = 1; i <= heap[0]; i++) {
        out << std::setw(3) << heap[i];
        if (i == newline) {
            out << endl;
            newline = newline * 2 + 1;
            gap = gap / 2;
            for (int j = 0; j < (gap - 1) / 2; j++) {
                out << filler;
            }
        } else {
            for (int j = 0; j < gap; j++) {
                out << filler;
            }
        }
    }

    out << endl << endl;

    newline = 1;
    for (int i = 1; i <= heap[0]; i++) {
        out << heap[i] << " ";
        if (i == newline) {
            out << endl;
            newline = newline * 2 + 1;
        }
    }
    out << endl << endl;
}

