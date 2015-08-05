#include <iostream>
using namespace std;

int main()
try { 
    cout << "Everything here will be caught";
} catch(...) {
    cout << "Catching..";
    return -1;
}