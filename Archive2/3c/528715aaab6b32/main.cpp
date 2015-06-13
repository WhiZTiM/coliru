#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

struct legit {
    int i;
    
    legit(int i): i(i) {}
};

legit fun(legit l) {
    cout << l.i << endl;
    return l; 
}

legit operator,(legit, legit r)
{ return r; }

int main()
{
    legit l = ((fun(1),fun(2)),fun(3));
    cout << "returned: " << l.i << endl;
    l = (fun(1),(fun(2),fun(3)));
    cout << "returned: " << l.i << endl;
}
