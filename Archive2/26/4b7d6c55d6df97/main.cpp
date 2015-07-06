#include <iostream>
#include <chrono>
#include <random>

template <typename T>
void printVector(const std::vector<T> &vec, std::ostream &output){
    for(auto &&element : vec){
        output << element << ", ";
    }
}

int main(){
    std::vector<int>
        source{1,2,3},
        destination(10,0);
        
    std::cout
        << "Destination: \n"
        << "\tsize: " << destination.size() << '\n'
        << "\tcapacity: " << destination.capacity() << '\n'
        << "\tcontents: \n";
    printVector<int>(destination, std::cout);
    
    std::cout << '\n';
    
    std::copy(source.begin(), source.end(), destination.begin() + 9);
    
    std::cout
        << "Destination: \n"
        << "\tsize: " << destination.size() << '\n'
        << "\tcapacity: " << destination.capacity() << '\n'
        << "\tcontents: \n";
    printVector<int>(destination, std::cout);
}