#include <iostream>
#include <string>
#include <vector>

// Tokenize a std::string given a list of tokens
std::vector<std::string> Tokenize(const std::string& _in, const std::string& _tokens)
{
    std::vector<std::string> toReturn;
    
    size_t stringStart = 0;
    size_t stringEnd = 0;
    std::string nextStr;
    while(stringStart < _in.size() && (stringEnd = _in.find_first_of(_tokens, stringStart)) != std::string::npos)
    {
        nextStr = _in.substr(stringStart, stringEnd-stringStart);
        if (!nextStr.empty())
        {
            toReturn.emplace_back(std::move(nextStr));
        }
        stringStart = stringEnd + 1;
    }
    
    if (stringStart < _in.size())
    {
        // push remainder of string into toReturn
        toReturn.emplace_back(_in.substr(stringStart));
    }
    
    return toReturn;
}


// helper function to print a vector
template<typename C>
void Print(C&& _in)
{
    for (auto&& val : _in)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

// test the implementation
int main()
{   
    // test the tokenize function
    // empty string, empty tokens
    std::cout << "Test1:\n";
    auto&& test1 = Tokenize(std::string(""), std::string(""));
    Print(std::forward<decltype(test1)>(test1));
    
    // empty string, non-empty tokens
    std::cout << "\nTest2:\n";
    auto&& test2 = Tokenize(std::string(""), std::string("](),"));
    Print(std::forward<decltype(test2)>(test2));
    
    // non-empty string, empty tokens
    std::cout << "\nTest3:\n";
    auto&& test3 = Tokenize(std::string("a,b,c,d,e,f"), std::string(""));
    Print(std::forward<decltype(test3)>(test3));
    
    // string, tokens, no tokens in string
    std::cout << "\nTest4:\n";
    auto&& test4 = Tokenize(std::string("a,b,c,d,e,f"), std::string("[] "));
    Print(std::forward<decltype(test4)>(test4));
    
    // adjacent tokens in string
    std::cout << "\nTest5:\n";
    auto&& test5 = Tokenize(std::string("a,,b,c,d,e,,f"), std::string(","));
    Print(std::forward<decltype(test5)>(test5));
    
    // special characters in string
    std::cout << "\nTest6:\n";
    auto&& test6 = Tokenize(std::string("a,b,c,\\,d,e,\",\n,f"), std::string(",\""));
    Print(std::forward<decltype(test6)>(test6));
    
    // normal case
     std::cout << "\nTest7:\n";
    auto&& test7 = Tokenize(std::string("a,b,c,d,e,f"), std::string(","));
    Print(std::forward<decltype(test7)>(test7));
    
    // trailing delimeters
    std::cout << "\nTest8:\n";
    auto&& test8 = Tokenize(std::string("a,b,c,d,e,f,"), std::string(","));
    Print(std::forward<decltype(test8)>(test8));
    
    // leading delimeters
    std::cout << "\nTest9:\n";
    auto&& test9 = Tokenize(std::string(",,a,b,c,d,e,f,"), std::string(","));
    Print(std::forward<decltype(test9)>(test9));
}
