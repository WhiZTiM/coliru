#include <algorithm>
#include <string>
#include <iostream>

int main() {
    std::string s = "Hello, World\t!\nHow's it\t going ?";
    std::string s2;
    
    std::cout << "Before :\n" << s << '\n';
    
    using std::begin; using std::end;
    s2.reserve(s.size());
    std::remove_copy_if(begin(s), end(s), std::back_inserter(s2), [](unsigned char ch) { return std::isspace(ch); });
    
    std::cout << "After :\n" << s2 << '\n';
    
    return 0;
}
