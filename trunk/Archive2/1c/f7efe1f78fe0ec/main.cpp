#include <iostream>
#include <string>
#include <vector>
#include <utility>

template <typename T>
void print(const T& _vec)
    {        
        for( auto c: _vec )
            std::cout << c << ",";
    }

typedef std::vector<std::string> vecstr_t;

struct Trade
{
    explicit Trade(vecstr_t&& vec) : _vec(std::move(vec))
    {       
    }  

     vecstr_t _vec;
};


int main()
{   
    vecstr_t tmpV = {"ONE", "TWO", "THREE", "FOUR"};    
    std::cout << "size 1:" << tmpV.size() << "\t"; print(tmpV); std::cout <<  "\n" ;    
    Trade t(std::move(tmpV));    
    std::cout << "size 2:" << tmpV.size() << "\t";  print(tmpV); std::cout <<  "\n" ; // expted tmpV should be e,pty but it has original contents    
    print(t._vec);    
}
