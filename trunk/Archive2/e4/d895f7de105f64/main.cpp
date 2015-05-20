#include<vector>
#include<chrono>
#include<algorithm>
#include<iostream>
enum TraversalOrder { RowMajor, ColumnMajor };
void sumMatrix(int *data, unsigned rows, unsigned columns,
long long& sum, TraversalOrder order)
{
    sum = 0;
    for (unsigned r = 0; r < rows; ++r) {
    for (unsigned c = 0; c < columns; ++c) {
    if (order == RowMajor)
    sum += data[r*columns + c];
    else
    sum += data[r + c*rows];
    }
    }
}

int main(){
    for(int i = 1; i <= 30; ++i){
        std::vector<int> vec(i * 1024 * 1024 / sizeof(int));
        long long sum;
        std::iota(vec.begin(), vec.end(), 0);
        auto start = std::chrono::high_resolution_clock::now();
        sumMatrix(vec.data(), vec.size() / 1024, 1024, sum, ColumnMajor);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << sum << '\t' << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << '\n';
    }
}