#include <cstdio>
#include <climits>

int main() {
    unsigned T,N,A,R,M;
    scanf("%u",&T);
    for(unsigned t=0;t<T;++t) {
        scanf("%u", &N);
        R=0;
        M=UINT_MAX;
        for(unsigned n=0;n<N;++n) {
            scanf("%u",&A);
            R+=A;
            if(A<M)
                M=A;
        }
        if(M>2)
            R -= (M-2);
        printf("%u\n",R);
    }
    
}