#include <type_traits>
#include <iostream>
#include <functional>

#include <unordered_map>
#include <cstring>
#include <boost/functional/hash.hpp>

struct LightStr
{
    std::string s_;
    const char* p_;
    LightStr(const char* p, bool own = true)
        : s_( own ? p : "" ) 
    {
        p_ = own ? s_.c_str() : p;
    }
};

struct LightStrEqualTo
{  
    bool operator()(const LightStr& l, const LightStr& r) const  
    { return strcmp( l.p_, r.p_ ) == 0; }  
};


struct LightStrHash
{
    size_t operator()(const LightStr& l)const
    {
        size_t h = 0;
        for(auto c = l.p_;*c;++c)
            boost::hash_combine(h, *c);
        return h;
    }
};

typedef std::unordered_map<LightStr, int, LightStrHash,  LightStrEqualTo > my_unordered_map;

int main()
{
    my_unordered_map m;
    LightStr i1("str1"); 
    m[i1] = 5;
    
    LightStr i2("str1", false);
    std::cout << m[i2];
    return 0;
    
}