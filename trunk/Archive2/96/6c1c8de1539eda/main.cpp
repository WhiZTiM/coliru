#include <iostream>
#include <climits>
#include <string>

#define C2(s) s"00", s"01", s"10", s"11"
#define C4(s) C2(s"00"), C2(s"01"), C2(s"10"), C2(s"11")
#define C6(s) C4(s"00"), C4(s"01"), C4(s"10"), C4(s"11")
#define C8(s) C6(s"00"), C6(s"01"), C6(s"10"), C6(s"11")


#ifdef __GNUC__

#define unlikely(x)     __builtin_expect(!!(x), 0)
#else
#define unlikely(x)     (x)

#endif


#define _big_endian_loop(it_name, value_name, ...)\
for (unsigned char const * it_name = (unsigned char *)(&value_name); it_name != (unsigned char *)(&value_name) + sizeof(value_name); ++it_name)\
{\
    __VA_ARGS__\
}


#define _little_endian_loop(it_name, value_name, ...)\
unsigned char const * it_name = (unsigned char *)(&value_name) + sizeof(value_name) -1;\
do\
{\
    __VA_ARGS__\
}\
while (it-- != (unsigned char *)(&value_name));


#ifdef __GCC__

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__\
#define _endian_loop(it_name, value_name, ...) _little_endian_loop(it_name, value_name, __VA_ARGS__)
#else
#define _endian_loop(it_name, value_name, ...) _big_endian_loop(it_name, value_name, __VA_ARGS__)
#endif

#else

#define _endian_loop(it_name, value_name, ...)\
union {uint8_t u8; uint16_t u16;} t;\
t.u16 = 1;\
if (t.u8)\
{\
    _little_endian_loop(it_name, value_name,  __VA_ARGS__)\
}\
else\
{\
    _big_endian_loop(it_name, value_name, __VA_ARGS__)\
}

#endif

#if (CHAR_BIT % 8 != 0)

#define LOOP_BEGIN(it_name, string_name)\
unsigned char slice = ((*it) >> (8 * (CHAR_BIT/8)));\
out.append(to_bin[slice]);

#else

#define LOOP_BEGIN(it_name, string_name) (void)0;

#endif


template <typename T>
std::string get_binary(const T& value)
{
    
    static char const * to_bin[] = {C8("")};
    
    std::string out;
    out.reserve(sizeof(value));
    
    _endian_loop(it, value, 
    {
        LOOP_BEGIN(it, out);
        
        for (int i = CHAR_BIT/8-1; i >= 0; --i)
        {
            unsigned char slice = ((*it) >> (8 * i));
            out.append(to_bin[slice]);
        }
    })
    
    return out;
    
}

int main() 
{
	std::uint32_t num = 10;
    std::cout << get_binary(num);
	return 0;
}