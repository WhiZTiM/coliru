// Behold the power of variadic templates
// Implements a CSV row creator

#include <string>
#include <iostream>

// The unary template form - for the last element in the row
template<typename T>
std::ostream& csvRow(std::ostream& os, const T& arg0)
{
    os << arg0 << std::endl;
    return os;
}

// the generic template form - for all other elements
template<typename T, typename... Types>
std::ostream& csvRow(std::ostream& os, const T& arg0, const Types&... args)
{
    os << arg0 << ',';
    return csvRow(os, args...);
}

int main()
{
    csvRow(std::cout, 1, 3.7, "Test", false, 3UL, "Test2", 0x1000);
    csvRow(std::cout, "A", std::string("B"), 42, "Null", 0UL, 3.141592654); 
    
    return EXIT_SUCCESS;
}