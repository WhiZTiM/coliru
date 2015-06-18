#include <iostream>
#include <string>

int main() {
    std::string arr[3];
    
    arr[0] = "abcdefg";

    arr[1] = "defghij";

    arr[2] = "ghijklm";
    
    
    for(size_t i = 0; i < 3; ++i) {
        for (auto it : arr[i]) {
            std::cout << it;
        }
        
        std::cout << '\n';
    }
    
    return 0;
}