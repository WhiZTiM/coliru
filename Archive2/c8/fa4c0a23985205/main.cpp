#include <iostream>
#include <string>
#include <vector>


int main()
{
    std::vector<char> table(127);
    table['!'] = 'a'; table['^'] = 'b'; table['&'] = 'c'; table['*'] = 'd'; table['@'] = 'e';
    table['('] = 'f'; table[')'] = 'g'; table['\''] = 'h'; table['#'] = 'i'; table['_'] = 'j';
    table['='] = 'k'; table['+'] = 'l'; table['['] = 'm'; table['{'] = 'n'; table['$'] = 'o';
    table[']'] = 'p'; table['}'] = 'q'; table[';'] = 'r'; table[':'] = 's'; table[','] = 't';
    table['%'] = 'u'; table['<'] = 'v'; table['.'] = 'w'; table['>'] = 'x'; table['/'] = 'y';
    table['?'] = 'z';

    std::string encrypted = ":%&&@::";
    std::string decrypted;
    for(size_t i = 0; i < encrypted.size(); ++i)
        decrypted += table[ encrypted[i] ];
    std::cout << decrypted << '\n';
}