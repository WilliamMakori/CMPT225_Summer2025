#ifndef MYFLOAT_HPP
#define MYFLOAT_HPP

#include <string>
#include <iostream>

class MyFloat{
public:
    // Constructors
    MyFloat();
    MyFloat(const std::string& input);
    
    // Big 3
    // YOUR CODE HERE
    
    // Addition operator
    MyFloat operator+(const MyFloat& other) const;
    
    // Comparison operators
    bool operator==(const MyFloat& other) const;
    bool operator!=(const MyFloat& other) const;
    
    // Friend functions (for input and output)
    friend std::ostream& operator<<(std::ostream& os, const MyFloat& f);
    friend std::istream& operator>>(std::istream& is, MyFloat& f);
    
    
private:
    // Data members
    short* integer;
    int integerLen;
    
    short* fractional;
    int fractionalLen;
    
    // helpers functions (YOU CAN ADD MORE HELPERS HERE)
    bool isValidNumber(const std::string& str) const;
    void parseFromString(const std::string& input);
    
};

#endif // MYFLOAT_HPP


