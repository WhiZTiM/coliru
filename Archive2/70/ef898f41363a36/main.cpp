#include <iostream>

#include <string>
#include <cstring>
#include <cstdint>
#include <cassert>

class Code2 {
    uint16_t mData;
    
    public:
        Code2() : mData(0x4141) {};
        
        Code2(const char* str, size_t len)
        {
            assert(len == 2);
            mData = (str[0] << 8) | str[1];
        }
        
        explicit Code2(const char* str)
        : Code2(str, strlen(str))
        {}

        explicit Code2(const std::string& str)
        : Code2(str.c_str(), str.size())
        {}
        

        explicit operator std::string() const
        {
            char tmp[2] = { char(mData >> 8), char(mData) };
            return std::string(tmp, 2);
        }
    
        friend bool operator==(Code2 lhs, Code2 rhs)
        {
            return lhs.mData == rhs.mData;
        }

        friend bool operator<(Code2 lhs, Code2 rhs)
        {
            return lhs.mData < rhs.mData;
        }
        
        friend std::ostream& operator<<(std::ostream& os, Code2 value)
        {
            char tmp[2] = { char(value.mData >> 8), char(value.mData) };
            os.write(tmp, 2);
            return os;
        }
        
};


int main()
{
    Code2 val1;
    Code2 val2("AB");
    Code2 val3(std::string("XZ"));
    Code2 val4("AA");
    
    using std::cout;
    
    cout << "Default constructed:     "  << val1 << '\n';
    cout << "C string constructed:    "  << val2 << '\n';
    cout << "std::string constructed: "  << val3 << '\n';
    
    assert(val1 < val2);
    assert(val1 < val3);
    assert(val1 == val4);
}
