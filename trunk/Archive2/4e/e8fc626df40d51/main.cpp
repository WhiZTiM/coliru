#include <iostream>
#include <assert.h>
using namespace std;

namespace __hidden__ {
    struct print {
        bool space;
        print() : space(false) {}
        ~print() { std::cout << std::endl; }
        
        template <typename T>
        print &operator , (const T &t) {
            if (space) std::cout << ' ';
            else space = true;
            std::cout << t;
            return *this;
        }
    };
    
    struct nrint {
        bool space;
        nrint() : space(false) {}
        ~nrint() { std::cout << std::endl; }
        
        template <typename T>
        nrint &operator , (const T &t) {
            if (space) std::cout << '\n';
            else space = true;
            std::cout << t;
            return *this;
        }
    };
    
}

#define erint __hidden__::print(),
#define nrint __hidden__::nrint(),

