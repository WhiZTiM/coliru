#include <iostream>
#include <string>
#include <regex>
#include <utility>

// extract tag and value from <tag>value</tag> and return a pair of strings{tag,value}
std::pair<std::string,std::string> extract( const std::string& text )
{
    static const std::string space = "\\s*" ; // zero or more spaces
    static const std::string letters = "(\\S+)" ; // capture group of one or more non-space chars
    
    // match "<tag>text</tag> "<(\S+)>(\S+)</\1>" 
    // with zero or more spaces (\s*) allowed between components
    std::regex re( R"#(\s*<\s*(\S+)\s*>\s*(\S+)\s*<\s*/\1\s*>\s*)#"  ) ;
    std::smatch match_results ;
    
    if( std::regex_match( text, match_results, re ) && match_results.size() == 3 )
        return { match_results[1].str(), match_results[2].str() } ;
    
    return {} ; // failed
}


int main()
{
    const std::string text[] = { "<baseQueueName>Hello</baseQueueName>", "< baseQueueName > Hello < /baseQueueName > ",
                                 "<amount>123.45</amount>", "  <  amount  >  123.45  </amount  >  ",
                                 "<baseQueueName>Hello</QueueName>", "<amount>123.45</Name>"};   
                                 
    for( const std::string& txt : text )
    {
         const auto pair = extract(txt) ;
         static const char quote = '"' ;
         std::cout << "text: " << quote << txt << quote ;
         if( !pair.first.empty() )
         {
            std::cout << "    tag: " << quote << pair.first << quote  
                      << "    value: " << quote << pair.second << quote << "\n\n" ;
         }
         else std::cerr << "    **** badly formed string ****\n\n" ;
    }
}