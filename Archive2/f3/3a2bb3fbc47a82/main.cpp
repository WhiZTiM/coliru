#include <iostream>

struct Tag{};

template <unsigned int i> constexpr
bool differsImpl(const Tag&, const char (&lhs)[i], const char (&rhs)[i]){
    return false;
}

template <unsigned int i, unsigned int RN> constexpr
bool differsImpl(const Tag&, const char (&lhs)[i], const char (&rhs)[RN]){
    return false;
}

template <unsigned int i, unsigned int LN> constexpr
bool differsImpl(const Tag&, const char (&lhs)[LN], const char (&rhs)[i]){
    return false;
}

template <unsigned int i, typename T, unsigned int LN, unsigned int RN> constexpr
bool differsImpl(const T&, const char (&lhs)[LN], const char (&rhs)[RN]){
    return (LN != RN) || (lhs[i] != rhs[i]) ||
        differsImpl<i+1>(Tag{}, lhs, rhs);
}

template <unsigned int i, unsigned int LN, unsigned int RN> constexpr
bool differs(const char (&lhs)[LN], const char (&rhs)[RN]){
    return differsImpl<i>('a', lhs, rhs);
}

template <unsigned int i, unsigned int LN, unsigned int RN> constexpr
bool equals(const char (&lhs)[LN], const char (&rhs)[RN]){
    return !differs<i>(lhs, rhs);
}

int main()
{
    
    // equal
    static_assert(true == equals<0>("A", "A"), "the impossible happened");
    static_assert(true == equals<0>("AB", "AB"), "the impossible happened");
    static_assert(true == equals<0>("ABBA", "ABBA"), "the impossible happened");
    static_assert(true == equals<0>("ACBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABB", "ACBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABB"), "the impossible happened");
    
    // different
    static_assert(true == differs<0>("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABB", "ACBA"), "the impossible happened");
    static_assert(true == differs<0>("A", "ACBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABB"), "the impossible happened");
    static_assert(true == differs<0>("AC\0zzzz", "ACa"), "the impossible happened");
    static_assert(true == differs<0>("ABBA", "ACBA"), "the impossible happened");
    static_assert(true == differs<0>("ABBAA", "ABBA"), "the impossible happened");
    static_assert(true == differs<0>("ABBA", "ABBAA"), "the impossible happened");
}
