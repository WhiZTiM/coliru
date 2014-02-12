#include <iostream>
#include <string>
#include <cctype>

int main()
{
    std::string input ;
    
    while( input.empty() )
    {
        std::cout << "please type in a string consisting of only alphanumeric characters\n" ;
        std::cin >> input ;
        
        // validate
        for( char c : input ) // for each character in input
        {
            if( !std::isalnum(c) ) // if it is not alphanumeric
            {
                std::cout << "invalid character '" << c << "' found in input '" << input << "'. please try again\n" ;
                input.clear() ; // make input empty so that we go through the loop again
                break ;
            }
        }
    }
    
    std::cout << "validated input is: '" << input << "'\n" ;
}
