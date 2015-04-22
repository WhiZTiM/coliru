#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct PointerCompare {
          bool operator()(const int* l, const int* r) {

	    	  if(*l==*r)
	    		  return (l<r);
	          return (*l<*r);
	      }
	    };
    
int main() {
    vector<int*> myValues(5);
    auto it = myValues.rbegin();
    *it = new int(4);
    ++it;
    int i = 0;
    for (; it != myValues.rend(); ++it) {
          *it = new int(++i);
    }
    
    std::sort(myValues.begin(), myValues.end(), PointerCompare());
    
    do {
        for (vector<int*>::iterator it = myValues.begin(); it != myValues.end(); ++it) {
            cout << ' ' << **it;
        }
        cout << endl;
    } while (next_permutation(myValues.begin(), myValues.end(), std::less<int*>()));
    
    myValues.clear();
}

