//
//
//class EquilateralTriangle{
//private:
//    float a;
//    //Wants to output these
//    // getters for the two variables
//    float circumference;
//    float area;
//    
//public:
//    void setA(float length){
//        a = length;
//        circumference = a*3;
//        area = (1.73 * a * a)/4;
//    }
//    
//    
//    friend class Homework; // friend class declaration
//    
//    
//};
//class Homework {
//public:
//    void PrintResults(EquilateralTriangle et){
//        // job is to print circumference and area of the triangle, what do we expect
//        cout << "circumference =" << et.circumference << endl;
//        cout << "area = " << et.area << endl;
//        
//    }
//};
//// Friendship is not inherited
//// Friendship is not mutual, the friend class's private and protected mmebers can't be accessed by the function who's friend it is.
//// Common with operator overloading, this is the case in the assignment question
//// Struct memnber functions are public, no friend fnctions needed
//// with classes and the members are public by default
//// instead of structures use classes

#include <iostream>
#include <list>

using namespace std;

int main(){
     
    // OOP practice
//    EquilateralTriangle et;
//    et.setA(3);
//
//    Homework h;
//    h.PrintResults(et);

    list<int> numbers = {1,2,3};
    numbers.push_back(4); // adds to the end of the list
    numbers.push_front(0); // adds to the front of the list
    
    list<int>::iterator it = numbers.begin();
    //advance.insert(it,10); what does this function do?
    for(int val: numbers){
        cout << val << " ";
    }
    
    cout << endl;
    
    return 0;
}

//Operator overloading


