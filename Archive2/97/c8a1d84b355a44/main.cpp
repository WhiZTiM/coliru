#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

long double convert(const char *);

class bad_number : public std::exception
{
public:
    bad_number(const char*);
    virtual const char* what() const noexcept;
private:
    const char* num;
};

bad_number::bad_number(const char * num) : num(num){ }
const char* bad_number::what() const noexcept
{
    std::string str;
    str.append("Invalid number format:");
    str.append(num);
    char* result = new char[str.size()];
    strcpy(result, str.c_str());
    return result;
}

long double convert(const char *str)
{
    char *endptr;
    double result = strtold(str, &endptr);
    if (*endptr != '\0')
        throw bad_number(str);
    return result;
}

int main(int argc, char ** argv)
{
    std::vector<long double> vect;
    for(int i = 1; i < argc; i++)
    {
        try{
            vect.push_back(convert(argv[i]));
        } catch (bad_number& e){
            std::cout << e.what() << std::endl;
        }
    }
}