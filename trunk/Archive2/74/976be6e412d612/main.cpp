#include <experimental/string_view>
#include <string>
#include <unordered_map>

using namespace std;
using namespace std::experimental; 

class sref { 
public: 
    mutable string_view sv; 
}; 
    
namespace std {
    
template<> class hash<sref> { 
public:
    size_t operator()(sref r) const { 
        return std::hash<string_view>()(r.sv); 
    } 
}; 
}

std::string *intern(string_view sv) { 
    static unordered_map<sref, std::string> um; 
    if(um.count(sref{sv})) { 
        return &um[sref{sv}]; 
    } 
    um[sref{sv}] = std::string(sv.begin(), sv.end()); 
    um.find(sref{sv})->first.sv = &um[sref{sv}]; 
    return intern(sv);
}
