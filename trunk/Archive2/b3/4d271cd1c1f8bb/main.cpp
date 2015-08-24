#include <iostream>
#include <map>
#include <utility>
#include <string>
#include <tuple>
#include <functional>

class JsonParser
{
    using Position = std::string::size_type;
    
    private:
        std::string str;
        std::string::size_type pos = 0;
        
        bool consume(char expected) {
            //std::cout << "consume         (" << str.substr(pos) << ", '" << expected << "')" << std::endl;
            
            if (pos+1 > str.size()) { return false; }
            if (str.at(pos) != expected) { return false; }
            ++pos;
            return true;
        }
        
        bool consume(const std::string& expected) {
            //std::cout << "consume         (" << str.substr(pos) << ", \"" << expected << "\")" << std::endl;
            
            if (pos+expected.size() > str.size()) { return false; }
            for (std::string::size_type i = 0; i < expected.size(); ++i) {
                if (str.at(pos+i) != expected.at(i)) { return false; }
            }
            pos += expected.size();
            return true;
        }
        
        std::tuple<bool, bool> parse_bool()
        {
            std::cout << "parse_bool      (" << str.substr(pos) << ")" << std::endl;
            
            bool ok = consume("TRUE");
            if (ok) { return std::make_tuple(true, true); }
            
            ok = consume("FALSE");
            if (ok) { return std::make_tuple(true, false); }
            
            std::cout << "Not a boolean." << std::endl; 
            return std::make_tuple(false, false);
        }
        
        std::tuple<bool, std::string> parse_string()
        {
            std::cout << "parse_string    (" << str.substr(pos) << ")" << std::endl;
    
            bool ok = consume('"');
            if (!ok) { std::cout << "String does not start with \"" << std::endl; return std::make_tuple(false, std::string()); };
            
            std::string::size_type new_pos = str.find_first_of('"', pos);
            if (new_pos == std::string::npos) { std::cout << "End of str." << std::endl; return std::make_tuple(false, std::string()); }
    
            std::string parsed_string = str.substr(pos, new_pos-pos);
            pos = new_pos;
            
            ok = consume('"');
            if (!ok) { std::cout << "String does not end with \"" << std::endl; return std::make_tuple(false, std::string()); }
    
            return std::make_tuple(true, parsed_string);
        }
        
        bool parse_pair()
        {
            std::cout << "parse_pair      (" << str.substr(pos) << ")" << std::endl;
    
            bool ok;
            std::string parsed_string;
            
            std::tie(ok, parsed_string) = parse_string();
            if (!ok) { return false; }
            
            ok = consume(':');
            if (!ok) { return false; }
            
            ok = parse_object();
            if (!ok) { return false; }
            
            return true;
        }
        
        bool parse_collection(char open, char close, std::function<bool()> parseElement)
        {
            std::cout << "parse_collection(" << str.substr(pos) << ")" << std::endl;
            
            bool ok = consume(open);
            if (!ok) { return false; };
            
            while (str.at(pos) != close)
            {
                ok = parseElement();
                if (!ok) { return false; }
                
                consume(',');
            }
            
            ok = consume(close);
            if (!ok) { return false; };
            
            return true;
        }
        
        bool parse_collection()
        {
            if (str.at(pos) == '[')
            {
                return parse_collection('[', ']', std::bind(&JsonParser::parse_object, this));
            }
            
            if (str.at(pos) == '{')
            {
                return parse_collection('{', '}', std::bind(&JsonParser::parse_pair, this));
            }
            
            return false;
        }
        
        bool parse_object()
        {
            //std::cout << "parse_object    (" << str.substr(pos) << ")" << std::endl;
            
            if (pos >= str.size())
            {
                return false;
            }
            
            switch (str.at(pos))
            {
                case '[':
                case '{':
                {
                    return parse_collection();
                }
                case '"':
                {
                    bool ok;
                    std::string parsed_string;
                    std::tie(ok, parsed_string) = parse_string();
                    return ok;
                }
                case 'T':
                case 'F':
                {
                    bool ok, parsed_bool;
                    std::tie(ok, parsed_bool) = parse_bool();
                    return ok;
                }
            }
            
            return false;
        }
        
    public:
        bool parse(const std::string& jsonStr)
        {
            str = jsonStr;
            return parse_object();
        }
};



int main()
{
    bool ok = JsonParser().parse("[[],[],[[{\"hola\":[FALSE,TRUE,FALSE]}]]]");
    std::cout << ok << std::endl;
}
