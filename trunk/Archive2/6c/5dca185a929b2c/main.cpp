#include <iostream>
#include <vector>
using namespace std;


template <typename X, typename Y>
auto f( X x, Y y ) {
    for( auto &i : x )
        cout << i*y << endl;
    return make_pair( x, y );
}

int main() {
    vector<int> v = {1,2,3,4,5,6};

    f( v, 10 );
}