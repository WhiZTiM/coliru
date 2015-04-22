#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
using namespace std;

struct PointerCompare {
    bool operator()(const int* l, const int* r) {
        return *l < *r;
    }
};
    
int main() {
    vector<int*> myValues(4);
    
    int i = 0;
    for (auto it = myValues.rbegin(); it != myValues.rend(); ++it) {
          *it = new int(++i);
    }
    
    do {
        for (vector<int*>::iterator it = myValues.begin(); it != myValues.end(); ++it) {
            cout << ' ' << **it;
        }
        cout << endl;
    } while (next_permutation(myValues.begin(), myValues.end(), std::less<int*>()));
    
    myValues.clear();
}

