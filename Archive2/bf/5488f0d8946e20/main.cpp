#include <iostream>
#include <sstream>

int main()
{
    std::istringstream file( R"(
148D
124D
225D
236D
259D
                              )" ) ;

    int number ;
    char throw_it_away ;
    while( file >> number >> throw_it_away ) std::cout << number << '\n' ;
}
