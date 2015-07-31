#include <iostream>
#include <string>
#include <vector>
#include <array>

typedef std::array<unsigned char, 81> sudoku;

int main() {
    
    std::vector<std::string> words = { "Using", "gcc", __VERSION__ };
    for(const auto& s: words) std::cout << s << ' ';
    std::cout << std::endl;

    sudoku stest =  {0,0,0, 0,0,0, 0,0,0,
                     0,0,0, 0,0,0, 0,0,0,
                     0,0,0, 0,0,0, 0,0,0,
                     0,0,0, 0,0,0, 0,0,0,
                     0,0,0, 0,0,0, 0,0,0,
                     0,0,0, 0,0,0, 0,0,0,
                     0,0,0, 0,0,0, 0,0,0,
                     0,0,0, 0,0,0, 0,0,0,
                     0,0,0, 0,0,0, 0,0,0};
            
    for(const auto& s: stest) std::cout << s << ' ';
    std::cout << std::endl;
}
