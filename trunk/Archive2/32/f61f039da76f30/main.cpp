#include <iostream>
#include <string>

static constexpr char vec[][5] = {"c", "miao", "biao", "liao", "gatt"};

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
    return (LN != RN) ||
        (lhs[i] != rhs[i]) ||
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

template <unsigned int i> constexpr
int index(const char (&arr)[5]){
    return equals<0>(vec[i], arr)?i:index<i-1>(arr);
}

template <> constexpr
int index<0>(const char (&arr)[5]){
    return equals<0>(vec[0], arr)?0:-1;
}

int textToTagImpl(const char* arr){
    for(auto i = 0u; i < 5u; ++i){
        if(std::string{arr} == vec[i]){
            return i;
        }
    }
    return -1;
}

int textToTag(const std::string& s){
    return textToTagImpl(s.c_str());
}

template <unsigned int N> constexpr
int textToTag(const char (&arr)[N]){
    return textToTagImpl(arr);
}

template <> constexpr
int textToTag<1>(const char(&arr)[1]){
    return index<sizeof(vec)/sizeof(vec[0]) - 1>({'\0', '\0', '\0', '\0', '\0'});
}

template <> constexpr
int textToTag<2>(const char(&arr)[2]){
    return index<sizeof(vec)/sizeof(vec[0]) - 1>({arr[0], '\0', '\0', '\0', '\0'});
}

template <> constexpr
int textToTag<3>(const char(&arr)[3]){
    return index<sizeof(vec)/sizeof(vec[0]) - 1>({arr[0], arr[1], '\0', '\0', '\0'});
}

template <> constexpr
int textToTag<4>(const char(&arr)[4]){
    return index<sizeof(vec)/sizeof(vec[0]) - 1>({arr[0], arr[1], arr[2], '\0', '\0'});
}

template <> constexpr
int textToTag<5>(const char(&arr)[5]){
    return index<sizeof(vec)/sizeof(vec[0]) - 1>(arr);
}

int main()
{
    static_assert(textToTag("c") == 0, "the impossible happened");
    static_assert(textToTag("miao") == 1, "the impossible happened");
    static_assert(textToTag("biao") == 2, "the impossible happened");
    static_assert(textToTag("liao") == 3, "the impossible happened");
    static_assert(textToTag("gatt") == 4, "the impossible happened");
    
#if 0
    static_assert(textToTag("gatto") == -1, "the impossible happened");
#else
    std::cout << "this should read -1: " << textToTag("gatto") << " (and cannot be evaluated at compile-time)" << std::endl;
#endif

    std::string miao{"miao"};
    std::cout << "this should read 1: " << textToTag(miao.c_str()) << " (and nobody would try to evaluate it at compile-time)" << std::endl;
}
