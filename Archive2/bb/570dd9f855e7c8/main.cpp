#include <iostream>
#include <type_traits>

//Scott Schurr's constexpr string with more stuff added to it
class str_const {
private:
    const char* const p_;
    const std::size_t sz_;
    
public:
    template<std::size_t N>
    constexpr str_const(const char(&a)[N]) : // ctor
    p_(a), sz_(N-1) 
    {}
    
    template<std::size_t N>
    constexpr bool operator==(const char (&rhs)[N]) const {
        if (this->size() != N - 1) {
            return false;
        }
        for (std::size_t i = 0; i < N - 1; ++i) {
            if (this->operator[](i) != rhs[i]) {
                return false;
            }
        }
        return true;
    }
    
    template<std::size_t N>
    constexpr str_const operator+(const char (&rhs)[N]) const {
        char new_str[size() + N] = {0};
        for (std::size_t i = 0; i < size(); ++i) {
            new_str[i] = p_[i];
        }
        for (std::size_t i = 0; i < N; ++i) {
            new_str[i] = rhs[i];
        }
        return str_const(new_str);
    }
    
    constexpr char operator[](std::size_t n) const { 
        return n < sz_ ? p_[n] :
        throw std::out_of_range("");
    }
    
    constexpr std::size_t size() const { 
        return sz_; 
    }
};

int main() 
{
    constexpr str_const str1 = "AAA";
    static_assert(str1 == "AAA", "Fail");
    constexpr str_const str2 = "ABC";
    static_assert(str1 + "DEF" == "ABCDEF", "Fail");
}