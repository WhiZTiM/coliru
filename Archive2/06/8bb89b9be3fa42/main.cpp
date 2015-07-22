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

int** constructSparseMatrix( int totalRow, int totalCol, int totalEl ) 
{
    int** arr = new int*[totalEl];

    for ( int **p = arr; p < arr + totalEl; ++p ) 
    {
        *p = new int[totalCol];
        for ( int *q = *p; q < *p + totalCol; ++q ) 
        {
            if ( q == *p + totalCol - 1 ) 
            {
                *q = rand () % 101;
            } 
            else 
            {
                *q = rand () % totalRow + 1;
            }
        }
    }

    return arr;
}

int main() {
    int totalEl = 5;
    int** arr = constructSparseMatrix(5,3,totalEl);
    for (int i = 0; i < totalEl; i++) {
		cout << "Insert: ("; 
		for (int k = 0; k < 3; k++) {
			if(k == 2) {
				cout << arr[i][k];
			} else {
				cout << arr[i][k] << ", ";
			}
		}
		cout << ")" << endl;
		cout << '\n';
	}

	delete [] arr;
}