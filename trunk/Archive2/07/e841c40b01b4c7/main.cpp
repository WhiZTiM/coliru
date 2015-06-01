#include <iostream>
#include <type_traits>

const int COL_SIZE = 7;
const int ROW_SIZE = 5;

double sum(double the_array[][COL_SIZE], int row, int col) {
    double sum =0;
    for (int i=0; i<row; i++) {
        for (int k=0; k<col; k++) {
            sum = sum + the_array[i][k];
        }
    }
    return sum;
}

int main() {
    double the_array[][7] = {
        {11.0, 2.9, 3.0, 4.0, 5.5, 6.0, 7.9},
        {12.0, 3.1, 3.0, 4.0, 5.5, 6.0, 7.9},
        {13.0, 2.9, 3.0, 4.0, 5.5, 6.0, 7.9},
        {14.0, 2.9, 3.0, 4.0, 5.5, 6.0, 7.9},
        {15.0, 2.9, 3.0, 4.0, 5.5, 6.0, 7.9},
    };
         
    double results = sum(the_array, 2,2);
    std::cout << results;
}