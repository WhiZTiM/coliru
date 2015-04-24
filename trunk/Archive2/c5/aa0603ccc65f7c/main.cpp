#include <cassert>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <array>
#include <tuple>




template<typename Head>
constexpr int sum_sizeof(Head head)
{
    return sizeof(head);
}

template<typename Head, typename ...Tail>
constexpr int sum_sizeof(Head head, Tail ...args)
{
    return sizeof(head) + sum_sizeof(args...);
}



using Port = std::uint16_t;
using IPv4 = std::array<uint8_t, 4>;


struct TCPSessionKey
{
    struct Fields
    {
        Port src_port, dst_port;
        IPv4 src_ip, dst_ip;
        uint8_t protocol;
    };
    
    TCPSessionKey() = default;
    
    TCPSessionKey(Fields inFields) : mStorage()
    {
        mStorage.mFields = inFields;
    }
    
    union Storage
    {
        uint64_t mFastKey;
        Fields mFields;
    };
    
    friend bool operator==(TCPSessionKey lhs, TCPSessionKey rhs)
    {
        return lhs.mStorage.mFastKey == rhs.mStorage.mFastKey;
    }
    
    friend bool operator!=(TCPSessionKey lhs, TCPSessionKey rhs)
    {
        return !(lhs == rhs);
    }
    
    friend bool operator<(TCPSessionKey lhs, TCPSessionKey rhs)
    {
        return lhs.mStorage.mFastKey < rhs.mStorage.mFastKey;
    }
    
    Storage mStorage;
};


int main()
{
    static_assert(std::is_pod<TCPSessionKey>::value, "");
    
    IPv4 src_ip = {{ 1, 2, 3, 4 }};
    IPv4 dst_ip = {{ 1, 2, 3, 5 }};
    
    TCPSessionKey a(TCPSessionKey::Fields{1, 2, src_ip, dst_ip, 22});
    TCPSessionKey b(TCPSessionKey::Fields{2, 3, src_ip, dst_ip, 33});
    
    std::cout << sizeof(TCPSessionKey::Fields) << std::endl;
    std::cout << sizeof(TCPSessionKey) << std::endl;
    
    assert(a == a);
    assert(a != b);
}
