#include <iostream>
#include <map>
#include <utility>
#include <string>
#include <tuple>


std::tuple<bool, std::string::size_type> parse(const std::string& str, std::string::size_type pos);



std::tuple<bool, std::string::size_type> consume(const std::string& str, std::string::size_type pos, const std::string& expected)
{
    std::cout << "consume(" << str << ", " << pos << ", " << expected << ")" << std::endl;
    
    if (pos+expected.size() > str.size())
    {
        return std::make_tuple(false, pos);
    }
    
    for (std::string::size_type i = 0; i < expected.size(); ++i)
    {
        if (str.at(pos + i) != expected.at(i))
        {
            return std::make_tuple(false, pos);
        }
    }
    
    return std::make_tuple(true, pos+expected.size());
}

std::tuple<bool, std::string::size_type> parse_list(const std::string& str, std::string::size_type pos)
{
    while (str.at(pos) != ']')
    {
        bool ok;
        std::tie(ok, pos) = parse(str, pos);
        if (!ok)
        {
            std::cout << "could not parse" << std::endl;
            return std::make_tuple(false, pos);
        }
        
        if (str.at(pos) != ',' && str.at(pos) != ']')
        {
            std::cout << "invalid next char: " << str.at(pos) << std::endl;
            return std::make_tuple(false, pos);
        }
        
        if (str.at(pos) == ',')
        {
            std::tie(ok, pos) = consume(str, pos, ",");
            if (!ok)
            {
                std::cout << ", expected" << std::endl;
                return std::make_tuple(false, pos);
            }
        }
    }
    return std::make_tuple(true, pos);
}

std::tuple<bool, std::string::size_type> parse(const std::string& str, std::string::size_type pos)
{
    std::cout << "parse(" << str << ", " << pos << ")" << std::endl;
    
    if (pos >= str.size())
    {
        return std::make_tuple(false, pos);
    }
    
    switch (str.at(pos))
    {
        case '[':
        {
            ++pos;
            bool ok;
            std::tie(ok, pos) = parse_list(str, pos);
            if (!ok)
            {
                std::cout << "could not parse list" << std::endl;
                return std::make_pair(false, pos);
            }
            
            std::tie(ok, pos) = consume(str, pos, "]");
            if (!ok)
            {
                std::cout << "] expected" << std::endl;
                return std::make_pair(false, pos);
            }
        }
    }
    
    return std::make_pair(true, pos);
}



int main()
{
    std::string str = "HOLAhola";
    
    bool ok;
    std::string::size_type pos;
    std::tie(ok, pos) = consume(str, 0, "HOLA");
    std::cout << ok << ' ' << pos << std::endl;
    
    std::tie(ok, pos) = parse("[[],[],[[]]]", 0);
    std::cout << ok << ' ' << pos << std::endl;
}
