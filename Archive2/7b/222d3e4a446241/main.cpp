#include <set>
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

int main() {
    set<int> testset({9, 7, 2, 8, 3, 5, 6, 1, 4, 0});
    copy(begin(testset), end(testset), ostream_iterator<int>(cout, " "));
    cout << '\n';
    copy(testset.begin(), testset.end(), ostream_iterator<int>(cout, " "));
}