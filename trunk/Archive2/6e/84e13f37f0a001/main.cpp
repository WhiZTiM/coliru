#include <cstdio>

template <typename T, void(*D)(T*)>
class Ptr
{
    T* p;
public:
    Ptr(T* p) : p(p) { }
    ~Ptr() { D(p); }
};

void _del_int(int* p)
{
    printf("deleting pointer %p to value %d\n", p, *p);
    delete p;
}

int main()
{
    Ptr<int, _del_int> x(new int(42));
}