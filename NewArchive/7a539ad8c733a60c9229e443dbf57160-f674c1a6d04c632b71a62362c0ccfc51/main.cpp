#include <array>
#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>


//
// Get max align from list of types.
//
template<typename ...Args>
struct MaxAlign;


template<typename T>
struct MaxAlign<T>
{
    enum : int {
        value = alignof(T)
    };
};

template<typename T, typename ...Args>
struct MaxAlign<T, Args...>
{
    enum : int {
        head_size = MaxAlign<T>::value,
        tail_size = MaxAlign<Args...>::value,
        value = head_size > tail_size ? head_size : tail_size
    };
};


//
// Get max type size from list of types
//
template<typename ...Args>
struct MaxSize;


template<typename T>
struct MaxSize<T>
{
    enum : int {
        value = sizeof(T)
    };
};


template<typename T, typename ...Args>
struct MaxSize<T, Args...>
{
    enum : int {
        head_size = MaxSize<T>::value,
        tail_size = MaxSize<Args...>::value,
        value = head_size > tail_size ? head_size : tail_size
    };
};


//
// Get index of T in Args
//
template<typename T, typename ...Args>
struct GetIndex;


template<typename T, typename ...Args>
struct GetIndex<T, T, Args...>
{
    enum { value = 0 };
};


template<typename T, typename U, typename ...Args>
struct GetIndex<T, U, Args...>
{
    enum { value = 1 + GetIndex<T, Args...>::value };
};



//
// Variant class
//
template<typename ...Args>
struct Variant
{
    template<typename T>
    Variant(T&& t) : type_index(GetIndex<T, Args...>::value)
    {
        new (data) T(std::forward<T>(t));
    }
    
    enum {
        alignment = MaxAlign<Args...>::value,
        size = MaxSize<Args...>::value
    };
    
    // main.cpp:81:71: error: requested alignment is not an integer constant
    //alignas(MaxAlign<Args...>::value) char data[MaxAlign<Args...>::value];
    
    // dirty work-around for missing alignas
    union
    {
        long long force_max_align;
        char data[size];
    };
    unsigned type_index;
};

template<typename T, typename ...Args>
const T& get(const Variant<Args...>& v)
{
    return *reinterpret_cast<const T*>(v.data);
}


template<typename T>
std::ostream& operator<<(std::ostream& os, const Variant<T>& v)
{
    return os << get<T>(v);
}


template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const Variant<T, U>& v)
{
    if (v.type_index == 0)
    {
        return os << get<T>(v);
    }
    else
    {
        return os << get<U>(v);
    }
}


template<typename T, typename U, typename V>
std::ostream& operator<<(std::ostream& os, const Variant<T, U, V>& v)
{
    if (v.type_index == 0)
    {
        return os << get<T>(v);
    }
    else if (v.type_index == 1)
    {
        return os << get<U>(v);
    }
    else
    {
        return os << get<V>(v);
    }
}


int main()
{
    std::cout << Variant<char, int, std::string>('c') << std::endl;
    std::cout << Variant<char, int, std::string>(42) << std::endl;
    std::cout << Variant<char, int, std::string>(std::string("Hello World!")) << std::endl;
}
