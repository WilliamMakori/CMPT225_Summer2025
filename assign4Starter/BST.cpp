#include <iostream>
#include <algorithm>
#include "BST.h"

using namespace std;

// This will catch memory leaks if run under Valgrind

// Default constructor
BST::BST(){
    root = new Node{-1, nullptr, nullptr};
}

// Big Three
// copy constructor 
BST::BST(const BST& other) {
    root = copyTree(other.root);
}
// assignment operator
BST& BST::operator=(const BST& other) {
    if (this != &other){
        deleteTree(root);
        root = copyTree(other.root);
    }
    return *this;
}
// destructor
BST::~BST() {
    deleteTree(root);
}

// Big Three Helpers
// delete tree
void BST::deleteTree(Node* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// copy tree
Node* BST::copyTree(Node* node) {
    if (node == nullptr)
        return nullptr;
    
    Node* newNode = new Node;
    newNode->key = node->key;
    
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    
    return newNode;
}

// Helper functions to print the tree 
void BST::printPretty(Node* node, string prefix, bool isLeft) const{
    if (node == nullptr || isExternal(node)) 
        return;
    
    if (node->right != nullptr && isInternal(node->right)) {
        printPretty(node->right, prefix + (isLeft ? "│   " : "    "), false);
    }
    
    cout << prefix;
    cout << (isLeft ? "└── " : "┌── ");
    cout << node->key << endl;
    
    if (node->left != nullptr && isInternal(node->left)) {
        printPretty(node->left, prefix + (isLeft ? "    " : "│   "), true);
    }
}
void BST::printPretty() const{
    printPretty(root, "", true);
}

// Testing node placement
bool BST::isExternal(Node* v) const{
    return v->left == nullptr && v->right == nullptr;
}
bool BST::isInternal(Node* v) const{
    return !isExternal(v);
}

// get height of tree 
int BST::getHeight() const {
    return getHeight(root);
}

int BST::getHeight(Node* node) const {
    // YOUR CODE HERE
    
    // if the node is a leaf, i.e the tree is empty
    if( node == nullptr)
        return 0;
    
    // leaf node, no children
    // not needed, this is done at the leftHeight and rightHeight parts
    if(isExternal(node))
        return 0;
    // if neither of the above are executed, we should go left and find the height of the left subtree
    
    int leftHeight = getHeight(node->left);
    
    // and go right to find the height of the right tree
    
    int rightHeight = getHeight(node->right);
    
    // one of these might be longer than the other, whichever one is longer contains the longest path, but why does removing 1 + max(left,right) return 0???
    
    // add the edge adjacent to either left or right tree, which ever is the longest
    return 1 + std::max(leftHeight, rightHeight);
    
}

// Searching for keys
Node* BST::treeSearch(int k, Node* v) const{
    // YOUR CODE HERE
    // if v is null or is an external node, v->left == NULL and v->right == NULL
    
    // if the value of k isn't found we should return the dummy node where it should've been
    // this is the base case
    if(!v || isExternal(v))
        return v;
    // if the value of k is the same as the key in v
    if(v->key == k )
    {
        return v;
    }
    // if k < v->key, the node is likely on the left side so go left
    else if (k < v->key)
        return treeSearch(k, v->left);
    // if k > v-> key, its node will be found on the right side so go right
    else {
        return treeSearch(k, v->right);
    }
}
bool BST::search(int val) const{
    return treeSearch(val, root)->key == val;
}

// Inserting key
void BST::insertAtExternal(Node* w, int k){
    w->key = k;
    w->left = new Node{-1, nullptr, nullptr};
    w->right = new Node{-1, nullptr, nullptr};
}
void BST::treeInsert(int k, Node* v) {
    Node* w = treeSearch(k,v);
    if(isExternal(w))
        insertAtExternal(w,k);
}
void BST::insert(int val) {
    treeInsert(val, root);
}
// Done
