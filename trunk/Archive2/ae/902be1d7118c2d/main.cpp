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

    for(int i = 0; i < row; i++) {
        arr[i] = new int[col];
        for (int k = 0; k < col; k++)
            arr[i][k] = arr[i][k] = rand () % 100;
    }
    return arr;
}

int main() {
    int size = 5;
    int** arr = constructSparseMatrix(size,3);
    for (int i = 0; i < size; i++) {
		cout << "Insert: ("; 
		for (int k = 0; k < 3; k++)
			cout << arr[i][k] << ',';
		cout << ")" << endl;
		cout << '\n';
	}
	
	delete [] arr;
}