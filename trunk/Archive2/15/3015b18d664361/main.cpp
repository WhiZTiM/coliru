#include <iostream>
#include <string>

struct UINT8 {
    typedef uint8_t value_type;
    static int Pack(const uint8_t &value) { std::cout << "Packing uint8_t of " << std::to_string(value) << std::endl; return 1; }
};

struct UINT16 {
    typedef uint16_t value_type;
    static int Pack(const uint16_t &value) { std::cout << "Packing uint16_t of " << value << std::endl; return 2; }
};


int PackArgs()
{
    return 0;
}

template<typename Arg1>
int PackArgs(const typename Arg1::value_type& arg1)
{
    return Arg1::Pack(arg1);
}

template<typename Arg1, typename Arg2, typename... Args>
int PackArgs(const typename Arg1::value_type& arg1, const typename Arg2::value_type& arg2, const typename Args::value_type&... args)
{
    int offset = Arg1::Pack(arg1);
    return offset + PackArgs<Arg2, Args...>(arg2, args...);
}


int main()
{
    uint8_t a = 5;
    uint16_t b = 20000;
    std::cout << "Packed " << PackArgs<UINT8, UINT16>(a, b) << " bytes" << std::endl;
}
