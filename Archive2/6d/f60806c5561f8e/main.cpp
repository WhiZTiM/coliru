#include <iostream>

template<const char* msg>
void display()
{
    std::cout << msg << std::endl;
}

// need to have external linkage 
// so that there are no multiple definitions
extern const char str1[] = "Test 1"; // (1)

// Why constexpr is enough? Does it have external linkage?
constexpr char str2[] = "Test 2";    // (2)

// Why doesn't this work? 
extern const char* str3 = "Test 3";  // (3) doesn't work

constexpr char* str4 = "Test 4"; // (4)

int main()
{
    display<str1>();    // (1')
    display<str2>();    // (2')
    // display<str3>(); // (3') doesn't compile 
    // display<str4>(); // (4') doesn't compile
}