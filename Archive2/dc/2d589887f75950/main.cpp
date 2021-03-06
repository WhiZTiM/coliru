#include <type_traits>

int make_some() { return 1; }

void serialize(int &x) {}

template<typename T>
T& unmove(T &&x)
{
    static_assert(std::is_same<std::remove_reference_t<T>, T>::value);
    return x;
}

int main()
{
    serialize(unmove(make_some()));
}