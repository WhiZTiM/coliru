#include <iostream>
#include <string>
#include <vector>

std::string g_string; // ;)
std::string g_string2;

template<typename DrawCallFn, typename... Args>
void CallFn(DrawCallFn fn, Args&... args)
{
    fn(args...);
}

void SaySomething(std::string &here)
{
    here = "Hello World!";
}

class Jerk
{
public:
    static void SaySomething(std::string &here)
    {
        here = "Your life has been a complete and utter waste";
    }
};

int main()
{
    CallFn(SaySomething,g_string);
    CallFn(Jerk::SaySomething,g_string2);
    std::cout << g_string << std::endl;
    std::cout << g_string2 << std::endl;

    return 0;
}
