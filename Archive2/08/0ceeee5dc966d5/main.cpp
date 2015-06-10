#include <memory>
#include <iostream>
#include <type_traits>

namespace suboptimal {
    
    template <typename T, typename D = std::default_delete<T>>
    class unique_ptr {
        T* ptr;
        D deleter;
    };

}

namespace ideal {
    
    template <std::size_t I, typename T,
        bool = std::is_empty<T>::value && !std::is_final<T>::value>
    class compressed_member : private T {
    public:
        constexpr T& get() noexcept { return *this; }
        constexpr T const& get() const noexcept { return *this; }
    };
    
    template <std::size_t I, typename T>
    class compressed_member<I, T, false> {
        T value_;
    public:
        constexpr T& get() noexcept { return value_; }
        constexpr T const& get() const noexcept { return value_; }
    };

    template <typename T1, typename T2>
    class compressed_pair
        : compressed_member<0, T1>
        , compressed_member<1, T2> {
    public:
        constexpr T1& first() noexcept { 
            return compressed_member<0, T1>::get();
        }
        constexpr T1 const& first() const noexcept {
            return compressed_member<0, T1>::get();
        }
        constexpr T1& second() noexcept { 
            return compressed_member<1, T2>::get();
        }
        constexpr T1 const& second() const noexcept {
            return compressed_member<1, T2>::get();
        }
    };
    
    template <typename T, typename D = std::default_delete<T>>
    class unique_ptr {
        compressed_pair<T*, D> m_;
    };

}
 
int main()
{
    std::cout << "sizeof \n"
        << " - int* : " << sizeof(int*) << '\n' // 8
        << " - std::default_delete<int> : "
        << sizeof(std::default_delete<int>) << '\n' // 1
        << " - suboptimal::unique_ptr<int> : "
        << sizeof(suboptimal::unique_ptr<int>) << '\n'; // 16
    std::cout << " - std::unique_ptr<int> : "
        << sizeof(std::unique_ptr<int>) << '\n'; // 8
    std::cout << " - ideal::unique_ptr<int> : "
        << sizeof(ideal::unique_ptr<int>) << '\n'; // 8
}