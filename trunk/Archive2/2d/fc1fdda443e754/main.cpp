#include <string>
#include <sstream>
#include <iostream>

int main()
{
    std::stringstream input;
    input
        << "Server: nginx\r\n"
        << "Date: Wed, 08 Jul 2015 12:12:25 GMT\r\n"
        << "Content-Type: application/json\r\n"
        << "Content-Length: 153\r\n"
        << "Connection: close\r\n"
        << "Access-Control-Allow-Origin: *\r\n"
        << "Access-Control-Allow-Credentials: true\r\n"
    ;
    
    std::string str;
    while (std::getline(input, str)) {
        auto index = str.find(':');
        std::pair<std::string,std::string> keyVal;
        if (index != std::string::npos) {
            keyVal = std::make_pair(
                str.substr(0,index),
                str.substr(index+1)
            );
            if (keyVal.second.front() == ' ') {
                keyVal.second.erase(0,1);
            } 
        }
        
        std::cout << keyVal.first << '|' << keyVal.second;
    }
}