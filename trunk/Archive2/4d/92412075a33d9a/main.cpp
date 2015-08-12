#include <iostream>
#include <string>
#include <sstream>

int main(int argc, char **argv) {
    if(argc < 2) {
        std::cerr << "No argument provided.\n";
        return 1;   
    }
    std::stringstream ss(argv[1]);
    bool b;
    
    if(!(ss >> std::boolalpha >> b)) {
        std::cerr << "Incorrect argument provided.\n";
        return 1;   
    }
    
    if(b)
        std::cout << "b is true\n";
    else
        std::cout << "b is false\n";
}