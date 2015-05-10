#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> numbers{"132", "99", "45", "999", "998", "989", "99"};

    sort(numbers.rbegin(), numbers.rend(), [](auto a, auto b) {

        bool s = a.size() <= b.size();
        if (!s) swap(a, b);

        auto p = mismatch(a.begin(), a.end(), b.begin(), b.end());

        if (p.first == a.end()) return s ? false : true;

        if (*p.first > *p.second)
            return s ? false : true;
        else
            return s ? true : false;

    });

    for (auto s : numbers) cout << s << ' ';
    cout << endl;
}