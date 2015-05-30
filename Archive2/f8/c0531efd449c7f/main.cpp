#include <iostream>
using namespace std;

#include <x86intrin.h>
#include <stdint.h>

typedef size_t upL_t;
typedef unsigned long long u64_t;

template <typename wtype>
void println_af(const wtype* A,upL_t L){
    if (L == 0){
        cout << "{}" << endl;
        return;
    }
    
    cout << "{";
    
    L--;
    for (upL_t c = 0; c < L; c++){
        cout << A[c] << ",";
    }
    cout << A[L] << "}" << endl;
}

__attribute__ ((noinline))
u64_t add_nr(u64_t* T,const u64_t* A,const u64_t* B,upL_t L,u64_t cin){
    char carry = (char)cin;
    for (upL_t c = 0; c < L; c++){
        carry = _addcarry_u64(carry,A[c],B[c],T + c);
    }
    return carry;
}

int main(){

    u64_t A[10];
    u64_t B[10] = {0,0,0,0,0,0,0,0,0,0};
    for (int c = 0; c < 10; c++){
        A[c] = (u64_t)0 - 1;
    }

    u64_t carry = 1;
    carry = add_nr(A,A,B,10,carry);

    println_af(A,10);
    cout << carry << endl;


}
