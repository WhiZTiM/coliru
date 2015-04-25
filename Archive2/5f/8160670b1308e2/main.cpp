#include <iostream>

using namespace std;

int main() {
    float f = 1.5;
    int i[3];
    i[2] = *(int *)&f;
    cout << *(float *)&i[2];

    return 0;
}