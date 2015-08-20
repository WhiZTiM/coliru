#include <boost/scope_exit.hpp>
#include <iostream>

class Logger
{
public:
    template<typename T>
    static void log(const std::string& s, const T& value)
    {
        std::cout << "in " <<  s << " value is: " << value << std::endl;
    }
};

int function(int v = 0)
{
    int result = 0;
    std::string name = __PRETTY_FUNCTION__;
    BOOST_SCOPE_EXIT(&name, &result)
    {
        Logger::log(name, result);
    } BOOST_SCOPE_EXIT_END
    if (v == 0)
    {
        result = 10;
        return result;
    }
    else if (v == 1)
    {
        result = 20;
        return result;
    }
    result = 30;
    return result;
}

int main()
{
    function();
    function(1);
    function(2);
}