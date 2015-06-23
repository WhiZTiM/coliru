#include <iostream>
using namespace std;

struct obj{
    int l;
    template<typename varname>
    varname operator[] (varname n){
        return (this->l)+n;
    }
};

int main(void){
    obj a;
    a.l=20;
    cout<<a[4];
    return 0;
}