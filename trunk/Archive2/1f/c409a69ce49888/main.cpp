#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <vector>
#include <utility>
#include <list>

using namespace std;

// using a function to achieve the same result:
int inc(int n)
{
    return ++n;
}

int main()
{
    typedef list<int> L;
    typedef L::const_iterator CI;
    typedef L::iterator I;
    L l {1,2,3,4,5,6,7};
    
    CI cb = l.begin(), ce = l.end();
    I b = l.begin();
    
    std::transform(cb, ce, b, inc);
    
    for (auto elem : l)
        cout << elem << endl;
}