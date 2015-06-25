#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <chrono>
#include <sstream>
#include <iostream>
using namespace std;
using namespace std::chrono;

typedef map<string, int> MyMapT;
typedef unordered_map<string, int> MyUMapT;

struct A {
    A() : m_values()
    {
        
    }
    
    vector<unique_ptr<string>> m_values;
}

int main() {

    /*
    auto t1 = system_clock::now();
    // algoritm call
    auto t2 = system_clock::now();

    cout << "Time: " << duration<double>(t2-t1).count() << endl;
    */

    /*vector<int> srcVec(10);

    iota( srcVec.begin(), srcVec.end(), 0 );

    random_device rd;
    mt19937 g( rd() );
    shuffle( srcVec.begin(), srcVec.end(), g );

    cout << "srcVec: [";
    copy( srcVec.cbegin(), srcVec.cend(), ostream_iterator<int>( cout, ", " ) );
    cout << "]" << endl;*/

    A a;

    return 0;
}