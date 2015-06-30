#include <deque>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    deque<int> di((istream_iterator<int>(cin)), (istream_iterator<int>()));
    copy(di.begin(), di.end(), ostream_iterator<int>(cout, " "));
}