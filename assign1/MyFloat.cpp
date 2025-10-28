#include "MyFloat.h"
#include <string>
#include <cctype>
#include <algorithm> // the max functions require this library
#include<iostream>

using namespace std;
// Default constructor
MyFloat::MyFloat() {
    
    integerLen = 1;
    integer = new short[integerLen];
    integer[0] = 0;
    
    fractionalLen = 1;
    fractional = new short[fractionalLen];
    fractional[0] = 0;
    
}

// Constructor that takes in a string object

MyFloat::MyFloat(const std::string& input) {
    // YOUR CODE HERE
    // Parsing logic for strings is in the parseFromString function
    
    
        if (isValidNumber(input)) {
            parseFromString(input);
        } else {
            integerLen = 1;
            fractionalLen = 1;
            integer = new short[integerLen]{0};
            
            fractional = new short[fractionalLen]{0};
            
            cout << "The string you entered isn't a valid number." << endl;
        }
    
    
}

// BIG 3 NEEDED
// Implement the destructor, copy constructor and assignment operators here
// Comparison operators

// Destructor
MyFloat::~MyFloat(){
    delete [] integer;
    delete[] fractional;
}

// Copy constructor
MyFloat::MyFloat(const MyFloat& other){
    
    // We're operating under the assumption that all the copying and the dynamic memory assignment has worked correctly
    
    // Copy the sizes
    integerLen = other.integerLen;
    fractionalLen = other.fractionalLen;
    
    // Allocate dynamic memory
    integer = new short[integerLen];
    fractional = new short[fractionalLen];
    
    // Copy the integer portion values
    
    for(int i = 0; i < integerLen; i++){
        integer[i] = other.integer[i];
    }
    
    //Copy the fractional portion values
    for(int j = 0; j < fractionalLen; j++){
        fractional[j] = other.fractional[j];
    }
}



// Assignment operator
MyFloat& MyFloat:: operator = (const MyFloat& other){
    // Self assignment check to make sure we don't delete the object
    if(this == &other){
        return *this;
    }
    
    // Free up the originally used dynamic memory
    delete[] integer;
    delete[] fractional;
    
    // Copy sizes
    
    integerLen = other.integerLen;
    fractionalLen = other.fractionalLen;
    
    // Allocate new memory
    
    integer = new short[integerLen];
    fractional = new short[fractionalLen];
    
    // Deep copy data
    for(int i=0; i<integerLen; i++){
        integer[i] = other.integer[i];
    }
    
    for(int j=0; j < fractionalLen; j++){
        fractional[j] = other.fractional[j];
    }
    
    return *this;
    
}

// Equality operator

bool MyFloat::operator==(const MyFloat& other) const {
    // YOUR CODE HERE
    if(integerLen != other.integerLen || fractionalLen != other.fractionalLen ){
        return false;
    }
    
    // Compare data now
    for(int i=0; i<integerLen; i++){
        if(integer[i] != other.integer[i])
            return false;
    }
    
    for(int i=0; i<fractionalLen; i++){
        if(fractional[i] != other.fractional[i])
            return false;
    }
    return true;
    
}
// Not equal operator
bool MyFloat::operator!=(const MyFloat& other) const {
    // YOUR CODE HERE
    // Making use of the == operator implementation
    // Does a deep comparison of the values
    return !(*this == other);
}

// Addition operator
MyFloat MyFloat::operator+(const MyFloat& other) const {
    // YOUR CODE HERE
    
    // Max fractional length and max integer length
    int maxFracLen = max(fractionalLen, other.fractionalLen);
    int maxIntLen = max(integerLen, other.integerLen);
    // Allocate new memory for all the four portions that will be used in the addition
    // Both of these will have padding on the right, example 0.7 will be 0.70 in the case that its being added to 0.35
    
    short* paddedFrac1 = new short[maxFracLen]();
    short* paddedFrac2 = new short[maxFracLen]();
    
    // Populate the allocated memory
    for(int i = 0; i < fractionalLen; i++){
        paddedFrac1[i] = fractional[i];
    }
    
    for(int i = 0; i <other.fractionalLen; i++){
        paddedFrac2[i] = other.fractional[i];
    }
    
    short* resultFrac = new short[maxFracLen];
    int carry = 0;
    // Add from right to left and account for the carried amount each time
    for(int i = maxFracLen-1; i >= 0; i-- ){
        int sum = paddedFrac1[i] + paddedFrac2[i] + carry;
        resultFrac[i] = sum%10;
        carry = sum/10;
    }
    // Should have the correct value at the end here, plus the amount to be carried over to the integer side
    
    
    short* paddedInt1 = new short[maxIntLen]();
    short* paddedInt2 = new short[maxIntLen]();
    
    for(int i = 0; i<integerLen; i++){
        paddedInt1[maxIntLen - integerLen + i] = integer[i];
    }
    
    for(int i = 0; i < other.integerLen; i++){
        paddedInt2[maxIntLen - other.integerLen + i] = other.integer[i];
    }
    
    // Add the integer parts from right to left as well
    short* resultInt = new short[maxIntLen + 1];
    int k = maxIntLen;
    for(int i = maxIntLen - 1; i>=0; i--, k--){
        int sum = paddedInt1[i] + paddedInt2[i] + carry;
        resultInt[k] = sum%10;
        carry = sum/10;
    }
    resultInt[k] = carry;
    
    // Final sizes
    int resultIntLen = maxIntLen + (carry ? 1 : 0);
    int resultFracLen = maxFracLen;
    
    // Create new MyFloat variable and copy the results of the addition into it
    
    MyFloat result;
    delete[] result.integer;
    delete[] result.fractional;
    
    result.integerLen = resultIntLen;
    result.fractionalLen = resultFracLen;
    
    result.integer = new short[resultIntLen];
    for(int i=0; i<resultIntLen; i++){
        result.integer[i] = resultInt[i+ (carry ? 0 : 1)];
    }
    result.fractional = new short[resultFracLen];
    for(int i=0; i < resultFracLen; i++){
        result.fractional[i] = resultFrac[i];
        
    }
    
    // Delete all the dynamically allocated memory to avoid memory leaks
    
    delete[] paddedFrac1;
    delete[] paddedFrac2;
    delete[] paddedInt1;
    delete[] paddedInt2;
    delete[] resultFrac;
    delete[] resultInt;
    
    // Pad the fractional parts
    return result;
}

// friend operator<< and operator>>
std::ostream& operator<<(std::ostream& os, const MyFloat& f) {
    for(int i = 0; i < f.integerLen; i++){
        os << f.integer[i];
    }
    os << '.';
    for(int i = 0; i < f.fractionalLen; i++){
        os << f.fractional[i];
    }
    return os;
}

std::istream& operator >> (std::istream& is, MyFloat& f) {
    std::string input;
    is >> input;
    
    // convert string to appropriate private data
    delete[] f.integer;
    delete[] f.fractional;
    
    // reuse logic
    // Check the validity of the input string
    if(f.isValidNumber(input)){
        f.parseFromString(input);
    }
    else{
        f.integerLen = 1;
        f.fractionalLen = 1;
        f.integer = new short[1]{0};
        f.fractional = new short[1]{0};
        
    }
    
    
    return is;
}
// validate input string

bool MyFloat::isValidNumber(const std::string& str) const {
    if (str.empty()) return false;
    
    int i = 0;
    
    bool hasDigitsBeforeDot = false;
    
    int len = str.length();
    
    while (i < len && std::isdigit(str[i])) {
        hasDigitsBeforeDot = true;
        i++;
    }
    
    // Optional decimal part
    
    if (i < len && str[i] == '.') {
        i++;
        bool hasDigitsAfterDot = false;
        while (i < len && std::isdigit(str[i])) {
            hasDigitsAfterDot = true;
            i++;
        }
        if (!hasDigitsBeforeDot && !hasDigitsAfterDot)
            return false; // e.g., "." with no digits
    }
    
    return i == len;
}
// why is this not a const function? 
void MyFloat::parseFromString(const std::string& input){
    // Find where the dot is first
    
    size_t dotPos = input.find('.');
    
    // Create the required substrings and use them to initiate the private variables
    
    std::string intPart = (dotPos == std::string::npos) ? input : input.substr(0, dotPos);
    std::string fracPart = (dotPos == std::string::npos) ? "" : input.substr(dotPos + 1);
    
    integerLen = intPart.size();
    fractionalLen = fracPart.size();
    
    integer = (integerLen > 0) ? new short[integerLen] : nullptr;
    fractional = (fractionalLen > 0) ? new short[fractionalLen] : nullptr;
    
    for (int i = 0; i < integerLen; i++) {
        integer[i] = intPart[i] - '0';
    }
    
    for (int i = 0; i < fractionalLen; i++) {
        fractional[i] = fracPart[i] - '0';
    }
}
int main(){
    
    // A default object with nothing in it, the print function should print 0.0
    // Before implementing anything else, the output operator works
    // The default constructor works
    // Lets start with the non default constructor
    
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
