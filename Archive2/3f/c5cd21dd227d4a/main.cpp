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
    vector<int*> myValues(3);
   

    for ( auto it = myValues.rbegin(); it != myValues.rend(); ++it) {
          *it = new int(0);
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

