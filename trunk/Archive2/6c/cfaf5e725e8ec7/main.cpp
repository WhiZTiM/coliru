#include <type_traits>
#include <string>
#include <iostream>
using namespace std;

typedef int Data;

struct Element 
{
    int i;
    int j;
    Data value;
};

int** constructSparseMatrix(int row, int col) {
    int** arr = new int*[row];
    int x = 0;
    for(int i = 0; i < row; i++) {
        arr[i] = new int[col];
        for (int k = 0; k < col; k++)
            arr[i][k] = x++;
    }
    return arr;
}

int main() {
    int size = 2;
    int** arr = constructSparseMatrix(size,3);
    for (int i = 0; i < size; i++) {
        for (int k = 0; k < 3; k++)
            std::cout << arr[i][k] << ' ';
        std::cout << '\n';
    }
}