#include<tuple>

    struct A { A(int) {} };
    struct B { B(int) {} };
    struct C { C(int) {} };

    template<typename ... T>
    auto init_tuple(T&& ... t)
    {
         return std::forward_as_tuple(std::forward<T>(t) ...);
    }
    
    template<typename T, size_t ... I>
    auto init_tuple(T&& t, std::index_sequence<I ...>)
    {
        return init_tuple((t) ...);
    }

    int main()
    {
        auto t = init_tuple(5,5,5); (void) t;
    }