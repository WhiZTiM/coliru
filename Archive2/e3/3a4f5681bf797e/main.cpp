#include <string>
#include <sstream>
#include <iostream>


int main(int argc, char** argv) {
    std::string s = "1 2 3 4 5 6 7 8 9 10";
    std::stringstream stream(s);
    int arr[10] = {0};
    for (auto & e : arr) {
        stream >> e;
    }
    for (auto e : arr) {
        std::cout << e << std::endl;
    }
    
}