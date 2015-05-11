#include <vector>
using namespace std;

struct A {
    union {
        vector<int> vi;
        vector<double> db;
    };
};

int main(){}