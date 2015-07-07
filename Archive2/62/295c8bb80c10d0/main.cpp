#include <vector>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <sstream>
#include <iostream>
#include <memory>
using namespace std;
using namespace std::chrono;

struct A
{
    A() = default;
    
    string m_a;
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