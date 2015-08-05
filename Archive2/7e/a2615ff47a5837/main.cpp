#include <iostream>
#include <string>
#include <sstream> // location of stringstream definition
#include <vector>

std::string reverse(const std::string &original){
    return std::string{original.rbegin(), original.rend()};
}  


void printReversed(int integer, double floatingPoint){
    std::ostringstream
        stream;
        
    stream << integer << ", " << floatingPoint;
    
    
    std::cout << reverse(stream.str()) << '\n';
}

template <typename Container_>
void printContainer(std::ostream &out, const Container_ &container){
    for(auto &&element : container){
        out << element << ", ";
    }
    out << "\n";
}


int main(){
    
    printReversed(17, 43.21);
    std::ostringstream
        stream;
        
    printContainer(stream, "never eat soggy waffles");
    
    std::cout << reverse(stream.str()) << "\n";
}