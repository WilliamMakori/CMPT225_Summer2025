#include "MyFloat.h"
#include "MyFloat.cpp"
#include <iostream>
using namespace std;
// The problem here is that the file that has the implementations isn't included here

int main() {
    // Create two MyFloat objects
    MyFloat a("0.1");
    MyFloat b("0.2");

    // Add them
    MyFloat result = a + b;

     // Print result
     std::cout << a << " + " << b << " = " << result << std::endl;

    // Comparison test
    MyFloat expected("0.3");
    std::cout << "Expected: " << expected << std::endl;

    if (result == expected) {
        std::cout << "Addition is correct!" << std::endl;
    } else {
        std::cout << "Addition is incorrect." << std::endl;
    }

   
    

    return 0;
}
