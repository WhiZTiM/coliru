#include <iostream>
#include <algorithm>

template <typename T>
T** create2DArray(unsigned nrows, unsigned ncols)
{
    T** ptr = new T*[nrows];  
    T* pool = new T[nrows*ncols]();  
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
void resize2DArray(T**& arr, unsigned nRows, unsigned nCols, unsigned newRows, unsigned newCols)
{
    T** newArray = create2DArray<T>(newRows, newCols);
    size_t minRows = std::min(nRows, newRows);
    size_t minCols = std::min(nCols, newCols);
    for (size_t i = 0; i < minRows; ++i)
        for (size_t j = 0; j < minCols; ++j)
            newArray[i][j] = arr[i][j];
    delete2DArray<T>(arr);
    arr = newArray;
}

using namespace std;

int main()
{
    unsigned nRows = 10;
    unsigned nCols = 10;
    double **dPtr = create2DArray<double>(nRows, nCols);
    dPtr[0][0] = 10;  // for example
    resize2DArray(dPtr, nRows, nCols, nRows+1, nCols+1);
    cout << dPtr[0][0];  // value is still there after resizing
    delete2DArray(dPtr);
}