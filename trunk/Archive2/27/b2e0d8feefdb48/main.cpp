#include <stdio.h>
#include <err.h>

using namespace std;

class cudaMathopts;
class cpuMathopts;

template <class T = cpuMathopts> // can only do the = in c++11
class Mathopts {};


template <>
class Mathopts<cudaMathopts>
{
public:
    template <typename T> void foo(T t) {}
};

template <>
class Mathopts<cpuMathopts>
{
public:
    template <typename T> void foo(T t) {}
};

template <>
void Mathopts<cudaMathopts>::foo<int>(int i)
{
    //blah
}

int main()
{
}
