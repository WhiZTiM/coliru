#include <iostream>
#include <string>
#include <fstream>

void print()
{
    std::string name ;
    std::cout << "name? " ;
    std::getline( std::cin, name ) ;

    std::string address ;
    std::cout << "address? " ;
    std::getline( std::cin, address ) ;

    std::ofstream file( "Student.txt", std::ios_base::app ) ;
    file << name << " @ " << address << '\n' ;
}

int main()
{
    print() ;
}
