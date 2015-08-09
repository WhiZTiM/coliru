#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
const int N = 8;
int A[] = {1, 2, 3, 4, 5, 6, 7, 8};
random_shuffle(A, A + N);
copy(A, A + N, ostream_iterator<int>(cout, " "));
// The printed result might be 7 1 6 3 2 5 4 8, 
//  or any of 40,319 other possibilities.
}