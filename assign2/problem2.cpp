#include <string>
#include <iostream>
#include <chrono>

using namespace std;

class SinglyLinkedList {
private:
    struct Node {
        std::string data;
        Node* next;
    };
    
    Node* head;
    int size;
    
public:
    SinglyLinkedList();
    ~SinglyLinkedList();
    void insertFront(const std::string& value);
    bool isEmpty() const;
    int getSize() const;
    void printList() const;
    
    // Big Three
    
    SinglyLinkedList(const SinglyLinkedList& other); // Non-default constructor
    
    SinglyLinkedList& operator=(const SinglyLinkedList& other);//Assignment operator, deep copy
    
    void clear(Node* node); // Destructor
    
    // Returns the number of nodes in the linkedlist
    int count();
    
    void insertBack(const string& value);
    
    void iterativeReversal();
    
    void recursiveReversal();
    
    void recursiveReversalHelper(Node* prev, Node* current);
    
};



// Constructor
SinglyLinkedList::SinglyLinkedList() : head(nullptr), size(0) {}

// Destructor
SinglyLinkedList::~SinglyLinkedList() {
    clear(head);
}

// Insert at front
void SinglyLinkedList::insertFront(const std::string& value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = head;
    head = newNode;
    size++;
}

// Is empty
bool SinglyLinkedList::isEmpty() const {
    return head == nullptr;
}

// Get size
int SinglyLinkedList::getSize() const {
    return size;
}

// Print list
void SinglyLinkedList::printList() const {
    Node* current = head;
    while (current) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "nullptr\n";
}

// Copy constructor
SinglyLinkedList::SinglyLinkedList(const SinglyLinkedList& other) : head(nullptr), size(0) {
    Node* current = other.head;
    Node** tail = &head;
    while (current) {
        *tail = new Node;
        (*tail)->data = current->data;
        (*tail)->next = nullptr;
        tail = &((*tail)->next);
        current = current->next;
        size++;
    }
}

// Assignment operator
SinglyLinkedList& SinglyLinkedList::operator=(const SinglyLinkedList& other) {
    if (this != &other) {
        clear(head);
        Node* current = other.head;
        Node** tail = &head;
        while (current) {
            *tail = new Node;
            (*tail)->data = current->data;
            (*tail)->next = nullptr;
            tail = &((*tail)->next);
            current = current->next;
            size++;
        }
    }
    return *this;
}

// Clear list
void SinglyLinkedList::clear(Node* node) {
    if (node == nullptr) return;
    clear(node->next);
    delete node;
}
// --------------- YOUR CODE HERE -------------------//

// Iterative version
void SinglyLinkedList::iterativeReversal(){
    // A->B->C->D->nullptr
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;
    // start at A, and store B as next
    // store A as
    while(current != nullptr){
        next = current->next;
        // Assign to B to next
        current->next = prev;
        // assign B to prev
        prev = current;
        // A is now previous
        current = next;
    }
    head = prev;
    
}


void SinglyLinkedList::recursiveReversal() {
    if (!head || !head->next) return;  // empty or single-node list is already reversed
    recursiveReversalHelper(nullptr, head);
}
// Helper functions
void SinglyLinkedList::recursiveReversalHelper(Node* prev, Node* current) {
    
    if (current == nullptr) {
        head = prev;
        return;
    }
    
    Node* next = current->next;
    current->next = prev;
    recursiveReversalHelper(current, next);
    
}

int main() {
    
    SinglyLinkedList list;
    
    for(int i = 0; i < 100; i++){
        list.insertFront(to_string(i));
        
    }
    
    list.printList();
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // Recursive function
    
    list.recursiveReversal();
    
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> duration = end - start;
    
    std::cout << "Time taken by the recursive version is: " << duration.count() << " seconds\n";
    
    cout <<"After reversing by recursion" << endl;
    
    list.printList();
    
    auto startIterative = std::chrono::high_resolution_clock::now();
    
    //Iterative function
    
    list.iterativeReversal();
    
    auto endIterative = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> durationIterative = endIterative - startIterative;
    
    std::cout << "Time taken by the iterative version is: " << durationIterative.count() << " seconds\n";
    
    cout << "After reversing again using iteration " << endl;
    
    list.printList();
    
    
    return 0;
}


