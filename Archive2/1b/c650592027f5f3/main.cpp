#include <iostream>
#include <map>

int main() {
    // Set up the problem...
    std::map<char, int> foo;
    foo['a'] = 11;
    foo['b'] = 22;
    foo['c'] = 33;
    foo['d'] = 44;
    
    // Obtain the value of the 'a' key...
    const int value = foo['a'];
    // Subtract that value from each element...
    for (auto& element : foo) {
        element.second -= value;
    }
    
    // Output the map to verify the result...
    for (auto& element : foo) {
        std::cout << element.first << ": " << element.second << "\n";
    }
    
    return 0;
}