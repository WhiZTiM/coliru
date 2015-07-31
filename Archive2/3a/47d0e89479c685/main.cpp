// string::find_last_of
#include <iostream>

struct X
{
    float x;
};

struct Y : public X
{
    float y;
};

void fx(X& x)
{
    std::cout << x.x << std::endl;
}
void fy(Y & y)
{
    fx(y);
    std::cout << y.y << std::endl;
}

int main ()
{
    X x; x.x = 10;
    Y y; y.x = 20; y.y = 30;
    fx(x);
    fy(y);
    return 0;
}