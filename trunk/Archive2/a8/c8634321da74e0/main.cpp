#include <iostream>
#include <string>

// Normally, I would pass std::strings by const ref instead of by value, what whatevs
// ("Keep it simple, stupid")
void blowMind(std::string, double, std::string, double);

// Note: Please, PLEASE don't do this at home.
#define wtf(a,b) blowMind(#a, a, #b, b)

int main()
{
    boolalpha(std::cout); // ADL at its finest :)
    std::cout.precision(50); // MOAR DIGITZ
    
    wtf(0.1 + 0.2, 0.3);
    
    double x = 3.141592653589793238; // close enough
    wtf(((x*x)*x)*x, (x*x)*(x*x));
    
    double y = 2.718281828, z = 1.41421356;
    wtf(x*(y+z), x*y+x*z);
}

void blowMind(std::string s1, double d1, std::string s2, double d2)
{
    std::cout << "True or false: " << s1 + " == " + s2 << "? " << (d1 == d2);
    std::cout << "\nHere's why:";
    std::cout << "\n" + s1 + " == " << d1;
    std::cout << "\n" + s2 + " == " << d2 << '\n' << std::endl;
}
