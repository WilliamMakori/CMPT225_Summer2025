#ifndef BST_H
#define BST_H
#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
};

class BST {
private:
    Node* root;

    // helper function 
    // print a pretty-ish version of the tree
    void printPretty(Node* node, string prefix = "", bool isLeft = true) const;

    // check if given node is external
    bool isExternal(Node* v) const;

    // check if given node is internal
    bool isInternal(Node* v) const;

    // recursively calculate the height of the tree
    // IMPLEMENT THIS FUNCTION!!   
    int getHeight(Node* node) const;

    // search for key k
    // IMPLEMENT THIS FUNCTION!!  
    Node* treeSearch(int k, Node* v) const;

    // insert key k at given node
    void insertAtExternal(Node* w, int k);

    // find position and insert key k in tree
    void treeInsert(int k, Node* v);

    // recursively delete all tree nodes 
    void deleteTree(Node* node);

    // recursively copy keys from all tree nodes 
    Node* copyTree(Node* node);

public:
    BST(); // default constructor 

    // Big Three
    // destructor
    ~BST();
    // copy constructor
    BST(const BST& other);
    // assignment operator
    BST& operator=(const BST& other);

    // insert val into tree, duplicates will 
    // not be added
    void insert(int val);

    // return true if val is in tree
    bool search(int val) const;

    // get the height of the tree
    int getHeight() const;

    // print a pretty-ish version of the tree
    void printPretty() const;

};
#endif