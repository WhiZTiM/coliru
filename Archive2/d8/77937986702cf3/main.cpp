// http://stackoverflow.com/questions/31724863/range-based-for-with-brace-initializer-over-non-const-values
#include<list>
#include<functional>
#include<array>

// In this code, I've extended my answer to the question above such
// that it supports constexpr which should allow loop unrolling.
//
// When switching on constexpr, I found lots of problems:
// std:: reference_wrapper isn't constexpr, so I just made my own clone
// std:: array::{begin,end} don't work either, but I just took the address
//     of &a.front() and (1+&a.back())
//
//
// Requires C++14, in order that the prefix increment can be constexpr and non-const

template<typename T>
struct ref_wrap_constexpr {
    T& x;
    constexpr ref_wrap_constexpr(T& x_) : x(x_) {}
    constexpr operator T& () const {
        return x;
    }
};
template<typename T>
constexpr ref_wrap_constexpr<T> ref(T& x) {
    return x;
}

template<typename T, std:: size_t N>
struct hold_array_of_refs {
    using vec_type = std:: array< ref_wrap_constexpr<T>, N >;
    vec_type m_v_of_refs;
    constexpr hold_array_of_refs(vec_type && v_of_refs) : m_v_of_refs(std::move(v_of_refs)) { }
    struct iterator {
        typename vec_type :: const_iterator m_it;
        constexpr iterator(typename vec_type :: const_iterator it) : m_it(it) {}
        constexpr bool operator != (const iterator &other) {
            return this->m_it != other.m_it;
        }
        constexpr iterator& operator++() { // prefix
            ++ this->m_it;
            return *this;
        }
        constexpr T& operator*() {
            return *m_it;
        }
    };

    constexpr iterator begin() const {
        return iterator(&m_v_of_refs.front());
    }
    constexpr iterator end() const {
        return iterator(1+&m_v_of_refs.back());
    }
};

template<typename... Ts>
using getFirstTypeOfPack = typename std::tuple_element<0, std::tuple<Ts...>>::type;


template<typename ...T>
constexpr auto ref_range(T&... args) -> hold_array_of_refs< getFirstTypeOfPack<T...> , sizeof...(args)> {
    return {{{ args... }}}; // Why does clang prefer three levels of {} ?
}

constexpr int test_if_constexpr_works() {
    int a = 10;
    int b = 100;
    int c = 1000;

    int i = 0;
    for(auto& l : ref_range(a,b,c)) {
        i+=l;
    }
    return i;
}

constexpr int test_if_constexpr_works(std::list<int>& a, std::list<int>& b, std::list<int>& c) {
    int i = 0;
    for(auto& l : ref_range(a,b,c)) {
        (void)l;
        ++i;
    }
    return i;
}

#include<iostream>
int main(void){
    std:: list<int> a,b,c;
    // print the addresses, so we can verify we're dealing
    // with the same objects
    std:: cout << &a << std:: endl;
    std:: cout << &b << std:: endl;
    std:: cout << &c << std:: endl;
    for(auto& l : ref_range(a,b,c)) {
        std:: cout << &l << std:: endl;
        l.sort();
    }
    static_assert(test_if_constexpr_works() == 1110, "the constexpr sum of ints didn't work correctly");
    static_assert(  test_if_constexpr_works(a,b,c) == 3, "");
}
