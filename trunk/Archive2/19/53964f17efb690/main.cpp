#include <cstdlib>
#include <iostream>
#include <regex>
#include <string>
#include <cstdlib>

class integer_validator
{
public:
    integer_validator(const char* const str);
    bool is_valid();
    long get_number();
private:
    bool valid;
    long result;
};

integer_validator::integer_validator(const char* const str)
{ 
    char *endptr;
    result = strtol(str, &endptr, 10);
    if(*endptr == '\0') valid = true;
    else valid = false;
}

bool integer_validator::is_valid()
{
    return valid;
}

long integer_validator::get_number()
{
    if(!valid)
        throw std::exception();
    return result;
}
int main ()
{
    integer_validator vv("123123");
    integer_validator v("123123a");
    std::cout << vv.get_number() << std::endl;
    std::cout << v.get_number() << std::endl;
}
