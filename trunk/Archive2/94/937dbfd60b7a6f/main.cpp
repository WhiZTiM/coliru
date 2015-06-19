#include <iostream>
#include <type_traits>

#define V1 1.2.3
#define V2 3.2.1

#define STRF2(var) #var
#define STRF(var) STRF2(var)

template<typename T, int N1, int N2>
bool constexpr compare_strings(T (&s1)[N1], T (&s2)[N2])
{
    if (N1 == N2)
    {
        int i(0); 
        while (i < N1) 
        {
            if (s1[i] != s2[i]) return false; 
            ++i;
        }
        return true; 
    }
    return false; 
}

int main()
{
    std::cout << compare_strings(STRF(V1), "123") << std::endl;
    std::cout << std::integral_constant<bool , compare_strings(STRF(V1), "1.2.3")>::value << std::endl;
}
