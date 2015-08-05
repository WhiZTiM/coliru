#include <stdio.h>
#include <err.h>

using namespace std;

class cudaMathopts;
class cpuMathopts;

template <class T = cpuMathopts> // can only do the = in c++11
class Mathopts {
    public:
    template <typename U> void foo(U t);
};

template <typename T> template<typename U>
void Mathopts<T>::foo(U i)
{
    //rflib need code
}

template <typename T> template<>
void Mathopts<T>::foo<float>(float i)
{
    //blah
}

template <> template<>
void Mathopts<cudaMathopts>::foo<int>(int i)
{
    //blah
}

int main()
{
}
