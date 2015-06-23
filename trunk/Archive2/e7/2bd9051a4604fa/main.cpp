//#include <type_traits>
//#include <functional>
//#include <iostream>
//#include <string>
//#include <vector>
//#include <queue>
//#include <thread>
//#include <chrono>
//#include <atomic>
#include <iostream>
//#include <future>
//#include <thread>
//#include <mutex>
//#include <unordered_map>
//#include <cassert>
//#include <sstream>
//#include <type_traits>
using namespace std;
#include <stdio.h>
#include <stdlib.h>

int main() {
    int** matrix = (int**)malloc(sizeof(int*) * 10);
    int i = 0;
    for (int** row = matrix; row != matrix + 10; ++row) {
        *row = (int*)malloc(sizeof(int) * 10);
        for(int* col = *row; col != *row + 10; ++col) {
            *col = i++;
        }
    }
    for (int** row = matrix; row != matrix + 10; ++row) {
        free(*row);
    }
    free(matrix);
    cout << matrix[3][3] << endl;
}