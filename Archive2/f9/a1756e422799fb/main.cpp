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
    
    constexpr char operator[](std::size_t n) const { 
        return n < sz_ ? p_[n] :
        throw std::out_of_range("");
    }
    
    constexpr std::size_t size() const { 
        return sz_; 
    }
};

template<std::size_t M, std::size_t N>
constexpr str_const str_const_concat(const char (&lhs)[M], const char (&rhs)[N]) {
    char new_str[M + N - 1] = {0};
    for (std::size_t i = 0; i < M - 1; ++i) {
        new_str[i] = lhs[i];
    }
    for (std::size_t i = 0; i < N; ++i) {
        new_str[M + i] = rhs[i];
    }
    return str_const(new_str);
}

template<std::size_t M, std::size_t N>
constexpr str_const str_const_concat(const str_const lhs, const str_const rhs) {
    char new_str[M + N + 1] = {0};
    for (std::size_t i = 0; i < M; ++i) {
        new_str[i] = lhs[i];
    }
    for (std::size_t i = 0; i < N; ++i) {
        new_str[M + i] = rhs[i];
    }
    return str_const(new_str);
}

template<std::size_t M, std::size_t N>
constexpr str_const str_const_concat(const char (&lhs)[M], const str_const rhs) {
    char new_str[M + N] = {0};
    for (std::size_t i = 0; i < M - 1; ++i) {
        new_str[i] = lhs[i];
    }
    for (std::size_t i = 0; i < N; ++i) {
        new_str[M + i] = rhs[i];
    }
    return str_const(new_str);
}

int main() 
{
    constexpr str_const s1 = "blah";
    static_assert(str_const_concat<5, s1.size()>("blah", s1) == "blahblah", "Fail");
    constexpr str_const s2 = "meh";
    static_assert(str_const_concat<s1.size(), s2.size()>(s1, s2) == "blahmeh", "Fail");
}