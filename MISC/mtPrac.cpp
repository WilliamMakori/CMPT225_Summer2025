#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::cin;
using std::endl;




template<typename T>

class StackWithMin {
    
private:
    // TO DO: add private data members
    vector<T> data;
    
    
    public:
    StackWithMin(); // Constructor, creates an empty stack
    
    
    void push(const T& item){
        // add to the top of the stack
        
    }
    
    // removes the top element
    T pop();
    
    // returns size in constant time
    int size() const{
        return data.size();
    }
    
    // size check
    bool isEmpty() const{
        
        return data.empty();
    }
    
    // returns smallest element,no constant time implementation, unless we use a specific implementation that gets the elements sorted after every new addition.
    
    T min() const;
    
    
};
int main(){

return 0;

}
