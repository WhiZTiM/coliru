#include <iostream>

struct Tag{};

template <unsigned int i> constexpr
bool differs(const Tag&, const char (&lhs)[i], const char (&rhs)[i]){
    return false;
}

template <unsigned int i, unsigned int RN> constexpr
bool differs(const Tag&, const char (&lhs)[i], const char (&rhs)[RN]){
    return false;
}

template <unsigned int i, unsigned int LN> constexpr
bool differs(const Tag&, const char (&lhs)[LN], const char (&rhs)[i]){
    return false;
}

template <unsigned int i, typename T, unsigned int LN, unsigned int RN=LN> constexpr
bool differs(const T&, const char (&lhs)[LN], const char (&rhs)[RN]){
    return (lhs[i] != rhs[i]) || differs<i+1>(Tag{}, lhs, rhs);
}

int main()
{
    // falses
    std::cout << differs<0>('a', "A", "A") << std::endl;
    std::cout << differs<0>('a', "AB", "AB") << std::endl;
    std::cout << differs<0>('a', "ABBA", "ABBA") << std::endl;
    std::cout << differs<0>('a', "ABBA", "ABBA") << std::endl;
    
    // trues
    std::cout << differs<0>('a', "ABBA", "ACBA") << std::endl;
    std::cout << differs<0>('a', "ABBAA", "ABBA") << std::endl;
    std::cout << differs<0>('a', "ABBA", "ABBAA") << std::endl;
}
