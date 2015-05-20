#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::vector<std::vector<int>>> matrix;
    
    for (int i = 0; i < 10; ++i) {
        matrix.push_back(std::vector<std::vector<int>>());
        
        for (int j = 0; j < 10; ++j) {
            matrix[i].push_back(std::vector<int>());
            
            for (int k = 0; k < 10; ++k) {
                ((matrix.at(i)).at(j)).push_back(i*100 + j*10 + k);   
            }
        }
    }
    
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 10; ++k) {
                std::cout << matrix.at(i).at(j).at(k) << std::endl;  
            }
        }
    }
    
    return 0;
}