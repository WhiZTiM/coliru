#include <iostream>
#include <map>
#include <utility>
#include <string>
#include <tuple>
#include <functional>

std::tuple<bool, std::string::size_type> parse(const std::string& str, std::string::size_type pos);



std::tuple<bool, std::string::size_type> consume(const std::string& str, std::string::size_type pos, char expected)
{
    std::cout << "consume(" << str.substr(pos) << ", \'" << expected << "')" << std::endl;
    
    if (pos+1 > str.size())
    {
        return std::make_tuple(false, pos);
    }
    
    if (str.at(pos) != expected)
    {
        return std::make_tuple(false, pos);
    }
    
    return std::make_tuple(true, pos+1);
}

std::tuple<bool, std::string::size_type> consume(const std::string& str, std::string::size_type pos, const std::string& expected)
{
    std::cout << "consume(" << str.substr(pos) << ", \"" << expected << "\")" << std::endl;
    
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

std::tuple<bool, std::string::size_type> parse_string(const std::string& str, std::string::size_type pos)
{
    std::cout << "parse_string(" << str.substr(pos) << ")" << std::endl;
    
    bool ok;
    std::tie(ok, pos) = consume(str, pos, '"');
    
    std::string::size_type new_pos = str.find_first_of('"', pos);
    if (new_pos == std::string::npos)
    {
        std::cout << "String does not finish with \"." << std::endl;
        return std::make_tuple(false, pos);
    }
    
    std::string parsed_string = str.substr(pos, new_pos-pos);
    
    pos = new_pos;
    std::tie(ok, pos) = consume(str, pos, '"');
    if (!ok)
    {
        std::cout << "\" expected" << std::endl;
        return std::make_tuple(false, pos);
    }
    
    return std::make_tuple(true, pos);
}

std::tuple<bool, std::string::size_type> parse_pair(const std::string& str, std::string::size_type pos)
{
    std::cout << "parse_pair(" << str.substr(pos) << ")" << std::endl;
    
    bool ok;
    std::tie(ok, pos) = parse_string(str, pos);
    std::tie(ok, pos) = consume(str, pos, ':');
    std::tie(ok, pos) = parse(str, pos);
    return std::make_tuple(true, pos);
}

std::tuple<bool, std::string::size_type> parse_collection(const std::string& str, std::string::size_type pos, std::function<std::tuple<bool, std::string::size_type>(const std::string&, std::string::size_type)> parse_element)
{
    std::cout << "parse_collection(" << str.substr(pos) << ")" << std::endl;
    
    while (str.at(pos) != ']' && str.at(pos) != '}')
    {
        bool ok;
        std::tie(ok, pos) = parse_element(str, pos);
        if (!ok)
        {
            std::cout << "could not parse" << std::endl;
            return std::make_tuple(false, pos);
        }
        
        if (str.at(pos) != ',' && str.at(pos) != ']' && str.at(pos) != '}')
        {
            std::cout << "invalid next char: " << str.at(pos) << std::endl;
            return std::make_tuple(false, pos);
        }
        
        if (str.at(pos) == ',')
        {
            std::tie(ok, pos) = consume(str, pos, ',');
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
    std::cout << "parse(" << str.substr(pos) << ")" << std::endl;
    
    if (pos >= str.size())
    {
        return std::make_tuple(false, pos);
    }
    
    switch (str.at(pos))
    {
        case '[':
        {
            bool ok;
            std::tie(ok, pos) = consume(str, pos, '[');
            
            std::tie(ok, pos) = parse_collection(str, pos, parse);
            if (!ok)
            {
                std::cout << "could not parse list" << std::endl;
                return std::make_pair(false, pos);
            }
            
            std::tie(ok, pos) = consume(str, pos, ']');
            if (!ok)
            {
                std::cout << "] expected" << std::endl;
                return std::make_pair(false, pos);
            }
            
            break;
        }
        case '{':
        {
            bool ok;
            std::tie(ok, pos) = consume(str, pos, '{');
            
            std::tie(ok, pos) = parse_collection(str, pos, parse_pair);
            if (!ok)
            {
                std::cout << "could not parse dict" << std::endl;
                return std::make_pair(false, pos);
            }
            
            std::tie(ok, pos) = consume(str, pos, '}');
            if (!ok)
            {
                std::cout << "} expected" << std::endl;
                return std::make_pair(false, pos);
            }
            
            break;
        }
        case '"':
        {
            bool ok;
            std::tie(ok, pos) = parse_string(str, pos);
            if (!ok)
            {
                std::cout << "could not parse string" << std::endl;
                return std::make_pair(false, pos);
            }
            
            break;
        }
        case 'T':
        {
            bool ok;
            std::tie(ok, pos) = consume(str, pos, "TRUE");
            if (!ok)
            {
                std::cout << "could not parse TRUE" << std::endl;
                return std::make_pair(false, pos);
            }
            break;
        }
        case 'F':
        {
            bool ok;
            std::tie(ok, pos) = consume(str, pos, "FALSE");
            if (!ok)
            {
                std::cout << "could not parse FALSE" << std::endl;
                return std::make_pair(false, pos);
            }
            break;
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
    
    std::tie(ok, pos) = parse("[[],[],[[{\"hola\":[FALSE,TRUE,FALSE]}]]]", 0);
    std::cout << ok << ' ' << pos << std::endl;
}
