#include <string>
#include <iostream>

int main()
{
    std::string s("access/2/NOTIF/PI/%24cname%3D/bldg/temp/s/2%24");
    
    auto first = s.find("%24");
    if(first != std::string::npos) {
        auto second = s.find("%24", first + 1);
        
        if(second != std::string::npos) {
            std::cout << s.substr(first + 3, second - (first + 3)) << '\n';
        }
    }
}
