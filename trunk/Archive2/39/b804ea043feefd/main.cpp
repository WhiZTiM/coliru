#include <type_traits>
#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class storage
{
    aligned_storage_t<sizeof(T)> buf;

    storage(storage&&) = delete;
public:
    storage()
    {
        new (buf) T{};
    }
    T &operator*()
    {
        return *static_cast<T*>(&buf);
    }
    void destroy()
    {
        (**this).~T();
    }
};

template<typename T, bool destructor>
struct conditional_storage_destructor 
{
    storage<T> x;
};

template<typename T>
struct conditional_storage_destructor<T, true> : protected storage<T>
{
    storage<T> x;

    ~conditional_storage_destructor()
    {
        x.destroy();
    }
};

template<typename T>
class wrapper
{
    conditional_storage_destructor<T, not is_trivially_destructible<T>::value> x;
public:
    T &operator*()
    {
        return *(x.x);
    }
};

int main()
{
    static_assert(is_trivially_destructible< wrapper<int> >::value);
    static_assert(not is_trivially_destructible< wrapper<vector<int>> >::value);

    cout << "executed" << endl;
}
