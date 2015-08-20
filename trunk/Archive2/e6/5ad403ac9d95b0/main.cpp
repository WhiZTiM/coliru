#include <iostream>
#include <string>
#include <vector>

template<typename Stream, typename T>
Stream& operator<<(Stream &os, const T &vec)
{
    for (auto b = std::begin(vec), e = std::end(vec); b != e; ++b)
    {
        if (b != std::begin(vec))
            os << ' ';
        os << *b;
    }
    return os;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, __PRETTY_FUNCTION__, "!"
    };
    std::cout << words << std::endl;
    
    return 0;
}
