/*
namespace std 
{
  template<class Char>
  struct char_traits;

  template<class T>
  struct allocator;

  template<class Char, class Traits, class Allocator>
  struct basic_string;
}
*/
/*
namespace std
{
    template <class > class char_traits;
    template <typename > class allocator;
    
    namespace __cxx11
    {
    template <typename _CharT, typename _Traits, typename _Alloc> class basic_string;
    //template <typename, typename, typename> class basic_string;
    }
    
      
}

namespace std
{
typedef std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > string;
}
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cinttypes>
#include <limits>

    template<typename _CharT>
    class ctype;

    template<> class ctype<wchar_t>;
    
    template<typename _CharT>
    class __ctype_abstract_base
    {
        int c;
    };
    
    template<typename _CharT>
    class ctype : public __ctype_abstract_base<_CharT>
    {
        int b;
    };
    
    template<>
    class ctype<wchar_t> : public __ctype_abstract_base<wchar_t>
    {
        int d;
    };


class Moon
{
    int size;
    class Crater;
};

class Moon::Crater
{
    int diameter;
};

/*
template<>
    class ctype<wchar_t> //: public __ctype_abstract_base<wchar_t>
    {
        int a;
    };
    */

/*
    int do_something(float x, unsigned y)
    {
        return (int)x + (int)y;
    }
    
    int funcXXX(int (*ABC)(float x, unsigned y))
    {
        int d = ABC(3.5, 3);
        return d;
    }
*/    
/*    int (*funcXXX(float, unsigned))(int (*ABC)(float x, unsigned y))
    {
        int d = ABC(3.5, 3);
        return nullptr;
    }*/



    enum smallenum: int16_t
    {
        A,
        B,
        C,
        D,
        E,
        F
    };

    enum senum
    {
        Ax,
        Bx,
        Cx
    };

const char* int64toa(int64_t value)
{
    static const int MAX_SZ = 22;
    static char text[MAX_SZ];
    
    snprintf(text, MAX_SZ, "%" PRIi64, value);
    return text; 
}

const char* uint64toa(uint64_t value)
{
    static const int MAX_SZ = 22;
    static char text[MAX_SZ];
    
    snprintf(text, MAX_SZ, "%" PRIu64, value);
    return text; 
}

int64_t GetInt64()
{
    const char* token = "-9223372036854775809";
    return strtoll(token, nullptr, 10);
}

uint64_t GetUInt64()
{
    const char* token = "18446744073709551615";
    uint64_t result = strtoull(token, nullptr, 10);
    return result;
}

int main()
{
    /*
    int64_t value =   -9223372036854775807;
    uint64_t value2 = 18446744073709551615;
                    //18446744073709551615
    std::uint64_t val = std::numeric_limits<std::uint64_t>::max();
    //18446744073709551616;
    const char* c = nullptr;
    std::string str("\0");
    
    const char* s = str.c_str();
*/    
     //std::cout << uint64toa(value2) << std::endl;
     std::cout << GetUInt64() << std::endl;

    std::cout << sizeof(senum) << std::endl;
     
    
    /*
    funcXXX(&do_something);
    */
    std::cout << "" << std::endl;
}
