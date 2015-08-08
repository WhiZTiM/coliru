#include <experimental/string_view>
#include <string>
#include <unordered_map>
#include <cstring>
#include <iostream>

using namespace std;
using namespace std::experimental; 

class sref { 
public: 
    mutable string_view sv; 
}; 
    
bool operator==(const sref& a, const sref& b) {
  return a.sv.size() == b.sv.size() && std::memcmp(a.sv.data(), b.sv.data(), a.sv.size()) == 0;
}

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
    um.find(sref{sv})->first.sv = um[sref{sv}]; 
    return intern(sv);
}

int main() {
  std::cout << intern("hello") << intern("hello") << intern("folks");   
}