#include <algorithm>
#include <string>
#include <iostream>

int main() {
    std::string s = "Hello, World\t!\nHow's it\t going ?";
    
    std::cout << "Before :\n" << s << '\n';
    
    using std::begin; using std::end;
    s.erase(std::remove_if(begin(s), end(s), [](unsigned char ch) { return std::isspace(ch); }), end(s));
    
    std::cout << "After :\n" << s << '\n';
    
    return 0;
}
