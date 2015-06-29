#include <iostream>
#include <cmath>
using namespace std;

struct A{
    int arr[10]{};  // initializes array with all 0's
};

int main() {
    A * a = new A;
    for (auto e : a->arr) // ranged based for loop to show all of the 0's
        cout << e << "\n";
    return 0;
}