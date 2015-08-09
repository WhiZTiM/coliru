#include <iostream>

int main() {
    std::string point = "( 15 , 14 )";  // we have a point in a particular format
    int x, y;  // Now, we want to parse x and y coordinates from point

    // Read formatted data from the given string
    if (sscanf(point.data(), "( %d , %d )", &x, &y) != 2) 
        throw std::runtime_error("Parsing failed");
    
    std::cout << "x = " << x << '\n';  // x = 15
    std::cout << "y = " << y << '\n';  // y = 14
}