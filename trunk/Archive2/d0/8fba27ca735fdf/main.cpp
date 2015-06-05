#include <iostream>
#include <vector>
#include <iterator>
#include <future>
#include <string.h>

using namespace std;

const int N = 8;

int index_from_rc(int r, int c)
{
    return (r * (N - 1)) + c;
}

int main(int argc, char **argv)
{
    int count = 0;
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j++) {
            cout << index_from_rc(i, j) << endl;
            count++;
        }
    }
    cout << "count is " << count << endl;
    return 0;
}
