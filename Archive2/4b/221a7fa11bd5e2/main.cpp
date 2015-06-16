#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>

std::string data = "1.5 2.5 3.5 4.5";

int main() {
    std::stringstream stream(data);
    
    std::vector<double> vec{
        std::istream_iterator<double>{stream},
        std::istream_iterator<double>{}
    };
    
    for(auto && d : vec)
        std::cout << d << ' ';
        
    std::cout << std::endl;
}
