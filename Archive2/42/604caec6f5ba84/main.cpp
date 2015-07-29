#include <memory>
#include <utility>
#include <tuple>
#include <type_traits>

template<class T>
using unqualify_t = std::remove_cv_t<std::remove_reference_t<T>>;

template<class Int, class T>
using make_integer_sequence_for = std::make_integer_sequence<Int, std::tuple_size<unqualify_t<T>>::value>;

template<class T>
struct construct_once_array
{
    template<class... CArgs>
    construct_once_array(std::piecewise_construct_t, CArgs&&... cargs)
        : _ptr(static_cast<T*>(::operator new(sizeof...(CArgs) * sizeof(T))))
        , _size(sizeof...(CArgs))
    {
        construct(std::make_integer_sequence<int, sizeof...(CArgs)>{}, std::forward<CArgs>(cargs)...);
    }
    
    T* begin() { return _ptr.get(); }
    T* end() { return begin() + _size; }
    
    T const* begin() const { return _ptr.get(); }
    T const* end() const { return begin() + _size; }
    
private:
    template<int... Is, class... CArgs>
    void construct(std::integer_sequence<int, Is...>, CArgs&&... cargs)
    {
        using swallow = int[];
        (void)swallow{ 0, (construct_single(make_integer_sequence_for<int, CArgs>{}, Is, std::forward<CArgs>(cargs)), void(), 0)... };
    }
    
    template<int... Is, class CArgs>
    void construct_single(std::integer_sequence<int, Is...>, int i, CArgs&& cargs)
    {
        using std::get;
        ::new (&_ptr[i]) T(get<Is>(std::forward<CArgs>(cargs))...);
    }

    std::unique_ptr<T[]> _ptr;
    int _size;
};

#include <iostream>

struct X
{
    int value;
    
    X(int i) : value(i) {}
    X() = delete;
    X(X const&) = delete;
    X(X&&) = delete;
};

int main()
{
    construct_once_array<X> blah(std::piecewise_construct, std::make_tuple(0), std::make_tuple(1), std::make_tuple(2));
    
    for(auto&& x : blah)
    {
        std::cout << x.value << "\n";
    }
}