#include <iostream>
#include <string>

bool in(char c, const std::string& str){
    return str.find(c) != std::string::npos;
}

void testSet(char c, const std::string& str){
    std::cout << c << " is " << (in(c,str) ? "" : "not ") << "in character set " << str << '\n';
}

int main(){
    testSet('2', "1234567890");
    testSet('e', "1234567890");
    testSet('!', "1234567890");
    testSet('c', "1234567890");
}
