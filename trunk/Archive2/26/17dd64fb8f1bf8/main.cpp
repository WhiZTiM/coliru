#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <sstream>
#include <cstdlib>

class invalid_input_exception : public std::exception
{
private:
    const char* input;
public:
    invalid_input_exception(const char *);
    const char* what() const noexcept;
};

invalid_input_exception::invalid_input_exception(const char * input) : input(input) { }

const char * invalid_input_exception::what() const noexcept
{
    std::string message;
    message.append("Occured on: ")
            .append(input);
    return message.c_str();
}

int main(int argc, char ** argv)
{
    const char* str = "Aaaaa";
    throw invalid_input_exception(str);
}

