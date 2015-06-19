template <typename T>
struct A;

template <>
struct A<int>
{
};

template <>
struct A<bool>
{
};

int main()
{
    A<int> a;
    A<bool> b;
    // A<long> c; // Błąd!
    
    (void)a,(void)b;
}
