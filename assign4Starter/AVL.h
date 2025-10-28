#ifndef AVL_H
#define AVL_H
#include <iostream>
using namespace std;

struct NodeAVL {
    int key;
    int height;
    NodeAVL* left;
    NodeAVL* right;
    NodeAVL* parent;
};

class AVL {
private:
    NodeAVL* root;

    // helper function 
    // print a pretty-ish version of the tree
    void printPretty(NodeAVL* node, string prefix = "", bool isLeft = true) const;

    // check if given node is external
    bool isExternal(NodeAVL* v) const;

    // check if given node is internal
    bool isInternal(NodeAVL* v) const;

    // Search for key k
    // IMPLEMENT THIS FUNCTION!!  
    NodeAVL* treeSearch(int k, NodeAVL* v) const;

    // Insert key k at given node
    void insertAtExternal(NodeAVL* w, int k);

    // find position and insert key k in tree
    void treeInsert(int k, NodeAVL* v);

    // set height of v given heights of children
    void setHeight(NodeAVL* v);

    // rebalance tree after insert of v
    void rebalance(NodeAVL* v);

    // given z, y, x determine the needed rotation and rotate
    // IMPLEMENT THIS FUNCTION!!  
    void restructure(NodeAVL* z, NodeAVL* y, NodeAVL* x);

    // perform a left rotation for the given x
    // IMPLEMENT THIS FUNCTION!!  
    void leftRotation(NodeAVL* x);

    // perform a right rotation for the given x
    // IMPLEMENT THIS FUNCTION!!  
    void rightRotation(NodeAVL* x);

    // recursively delete all tree nodes 
    void deleteTree(NodeAVL* node);

    // recursively copy keys from all tree nodes 
    NodeAVL* copyTree(NodeAVL* node, NodeAVL* parent = nullptr);

public:

    AVL(); // default constructor 

    // Big Three
    // destructor 
    ~AVL(); 
    // copy constructor
    AVL(const AVL& other);
    // assignment operator
    AVL& operator=(const AVL& other);

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
