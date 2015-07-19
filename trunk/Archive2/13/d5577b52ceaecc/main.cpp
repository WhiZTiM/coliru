#include <iostream>
using namespace std;

#define debug(...) do {cerr << #__VA_ARGS__ << ": "; dbg,__VA_ARGS__; cerr << endl;} while(0)

struct debugger {
    template<typename T>
    debugger& operator,(const T& v) {    
        cerr << v << " ";    
        return *this;    
    }
} dbg;

int main() {
    int a = 2;
    string b("Quora");
    double c = 5.34;
    debug(a, b, c);
}