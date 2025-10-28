#include <stack>
#include <stdexcept>
#include <iostream>

using std::cout, std::endl, std::boolalpha;

template <typename T>
class Queue {
private:
    std::stack<T> inStack;
    std::stack<T> outStack;

    void shiftStacks(); // Move elements from inStack to outStack if needed

public:
    Queue() = default;

    void enqueue(const T& value);
    void dequeue();
    T front() const;
    bool isEmpty() const;
    int size() const;
};


template <typename T>
void Queue<T>::enqueue(const T& value) {
    inStack.push(value);
}

template <typename T>
void Queue<T>::dequeue() {
    
    shiftStacks();
    if (outStack.empty()) throw std::underflow_error("Queue is empty");
    outStack.pop();
    
}

template <typename T>
T Queue<T>::front() const {
    // const_cast used for shift logic
    const_cast<Queue*>(this)->shiftStacks();
    if (outStack.empty()) throw std::underflow_error("Queue is empty");
    return outStack.top();
}

template <typename T>
bool Queue<T>::isEmpty() const {
    return inStack.empty() && outStack.empty();
}

template <typename T>
int Queue<T>::size() const {
    return inStack.size() + outStack.size();
}

template <typename T>
void Queue<T>::shiftStacks() {
    if (outStack.empty()) {
        while (!inStack.empty()) {
            outStack.push(inStack.top());
            inStack.pop();
        }
    }
}


int main() {
    Queue<std::string> q;

    q.enqueue("A");
    q.enqueue("B");
    q.enqueue("C");

    cout << "Front: " << q.front() << endl; // A
    q.dequeue();

    cout << "Front: " << q.front() << endl; // B
    q.dequeue();

    cout << "Is empty? " << boolalpha << q.isEmpty() << endl; // false

    q.dequeue();

    cout << "Is empty? " << boolalpha << q.isEmpty() << endl; // true

    return 0;
}

