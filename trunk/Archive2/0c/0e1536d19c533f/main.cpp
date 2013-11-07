#include <unordered_set>
#include <map>
#include <vector>
#include <list>
#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <functional>
#include <cassert>

using namespace std;
using namespace std::placeholders;


int main()
{
    hash<int> h;
    for( int i=0 ; i<15 ; ++i )
    {
        cout << "int hash for " << i << " is " << h(i) << endl; 
    }

    hash<string> hs;
    for( int i=0; i<15; ++i) {
        stringstream ss;
        ss << i;
        cout << "string hash for " << i << " is " << hs(ss.str()) << endl; 
    }
}