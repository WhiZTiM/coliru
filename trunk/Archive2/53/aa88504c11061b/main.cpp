
#include <iostream>
#include <map>
#include <string>

std::string s1("one");
std::string s2("two");
std::string s3("three");
std::string s4("four");

class X
{
    typedef std::map<std::string, std::string> MyMapType;
    MyMapType map1 = { { s1, s2 }, { s3, s4 } };
    MyMapType map2 = { { std::make_pair(s1, s2) }, { std::make_pair(s3, s4) } };
};

int main()
{
}