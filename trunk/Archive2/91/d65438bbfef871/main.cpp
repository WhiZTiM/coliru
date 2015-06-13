#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

int fun(int i) {
    cout << i << endl;
    return i; 
}

int main()
{
    int i = ((fun(1),fun(2)),fun(3));
    cout << "returned: " << i << endl;
    i = (fun(1),(fun(2),fun(3)));
    cout << "returned: " << i << endl;
}
