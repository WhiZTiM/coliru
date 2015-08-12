#include <cstdio>

template<int z>
struct s
{
    enum{e = (z%3==0) ? s<z/3>::e : (z==1 ? 1 : 0)};
};

int main(){
    printf("%d\n",s<91>::e);
    return 0;
};