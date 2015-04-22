#include <string>

int main()
{
    using namespace std::literals::string_literals;
    return ("hello"s + "world!"s).size();
}
