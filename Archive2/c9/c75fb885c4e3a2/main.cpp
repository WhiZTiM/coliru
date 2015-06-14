#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
    int y;
    cout << "Enter number of elements of array: ";
    cin >> y;
    int x[y];   // I declared an array using a variable size instead of a constant expression
    x[y-1] = 3;
    cout << x[y-1];

    return 0;
}
