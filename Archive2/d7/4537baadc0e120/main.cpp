#include <iostream>
#include <map>

int main() {
    std::map<char, int> foo;
    foo['a'] = 11;
    foo['b'] = 22;
    foo['c'] = 33;
    foo['d'] = 44;
    
    const int value = foo['a'];
    for (auto& element : foo) {
        element.second -= value;
    }
    
    for (auto& element : foo) {
        std::cout << element.first << ": " << element.second << "\n";
    }
    
    return 0;
}