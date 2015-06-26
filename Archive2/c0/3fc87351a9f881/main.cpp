#include <iostream>
#include <algorithm>

template <typename T>
T** create2DArray(unsigned nrows, unsigned ncols)
{
    T** ptr = new T*[nrows];  // allocate pointers
    T* pool = new T[nrows*ncols]();  // allocate pool
    for (unsigned i = 0; i < nrows; ++i, pool += ncols)
        ptr[i] = pool;
    return ptr;
}

template <typename T>
void delete2DArray(T** arr)
{
    delete[] arr[0];  // remove the pool
    delete[] arr;     // remove the pointers
}

template <typename T>
T** resize2DArray(T** arr, unsigned nRows, unsigned nCols, unsigned newRows, unsigned newCols)
{
    T** newArray = create2DArray<T>(newRows, newCols);
    size_t minRows = std::min(nRows, newRows);
    size_t minCols = std::min(nCols, newCols);
    for (size_t i = 0; i < minRows; ++i)
        for (size_t j = 0; j < minCols; ++j)
            newArray[i][j] = arr[i][j];
    delete2DArray<T>(arr);
    return newArray;
}

using namespace std;

int main()
{
    double **dPtr = create2DArray<double>(10, 10);
    dPtr[0][0] = 10;  // for example
    dPtr = resize2DArray(dPtr, 10, 10, 20, 20);
    dPtr[19][19] = 30;  // for example
    cout << dPtr[19][19];
    delete2DArray(dPtr);
}