
template<typename T>
struct ReallyVerboseName
{
    ReallyVerboseName(T const &){}
    virtual ~ReallyVerboseName() = default;
};

template<typename T>
struct Derived1
: virtual ReallyVerboseName<T>
{
    using RVN_t = ReallyVerboseName<T>;
    virtual ~Derived1() = 0;
};
template<typename T>
Derived1<T>::~Derived1<T>() = default;

template<typename T>
struct Derived2
: Derived1<T>
{
    using typename Derived1<T>::RVN_t ; // *** added
    Derived2(T const &t)
    : RVN_t(t) // now, RVN_t is a dependant name
    {
    }
};

int main()
{
    Derived2<int>{7};
}
