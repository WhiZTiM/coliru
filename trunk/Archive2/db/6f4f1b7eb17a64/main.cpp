#include <iostream>
#include <boost/units/unit.hpp>

void test2()
{
    int i = 0;
    i++;
}

void test()
{
    test2();
}

void asd()
{
    test();
    asd();
}

int main(int argc, char* argv[])
{
    asd();
}
