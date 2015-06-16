#include <type_traits>

template<typename T>
T& unmove(T &&x)
{
    static_assert(std::is_same<std::remove_reference_t<T>, T>::value);
    return x;
}

int make_some() { return 0; }

void serialize(int &x) {}

int main()
{
    serialize(unmove(make_some()));
}
