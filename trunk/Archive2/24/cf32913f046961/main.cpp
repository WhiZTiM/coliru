//http://codegolf.stackexchange.com/questions/49638/not-your-routine-bean-machine?noredirect=1#comment117290_49638
#include <stdio.h>
int main() {
    float d[9999]={1},o,n=1;
    int i=0,m=0;
    char c;
    for(;o=n,n=d[i+1],scanf("%c",&c)+1;++i) {
        if(c=='^'){d[i]-=o/2;d[i+1]+=o/2;}
        if(c=='\\'){d[i]-=o;d[i+1]+=o;}
        if(c=='\n'){m=i;i=-1;n=d[0];}
    }
    for(;i<=m;++i)
        printf("%f ",d[i]);
}