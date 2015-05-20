#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::vector<int>> matrix;
    
    for (int i = 0; i < 10; ++i) {
        matrix.push_back(std::vector<int>());
        for (int j = 0; j < 10; ++j) {
            matrix[i].push_back(i*10 + j);   
        }
    }
    
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            std::cout << matrix[i].at(j) << std::endl;
        }
    }
    
    return 0;
}