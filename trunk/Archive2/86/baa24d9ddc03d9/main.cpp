#include <iostream>
#include <bitset>
#include <limits>

int main()
{
    int y = 0 ;
   
    
    std::bitset<sizeof(int)*8> blow(static_cast<unsigned long>(std::numeric_limits<int>::lowest())) ;
    std::bitset<sizeof(int)*8> bhigh( static_cast<unsigned long>(std::numeric_limits<int>::max()) ) ;
    std::cout << "int\t"
              << std::numeric_limits<int>::lowest() << '\t'
              << std::numeric_limits<int>::max() 
                  << "\t" << (~std::numeric_limits<int>::max()) 
               << "\t" << (-~std::numeric_limits<int>::max()) 
                  <<  '\n';
    std::cout << blow << "\n" << bhigh << std::endl << std::endl ;;
    
    std::bitset<sizeof(int)*8> b1( static_cast<unsigned long>(y) ) ;
    std::bitset<sizeof(int)*8> b2( static_cast<unsigned long>(~y) ) ;
    std::bitset<sizeof(int)*8> b3( static_cast<unsigned long>(-~y) ) ;
    
    std::cout << y << " " << (~y) << " " << (-~y) << std::endl ;
    std::cout << b1 << "\n" << b2 << "\n" << b3 << std::endl ;
    
    y = 1 ;
    std::bitset<sizeof(int)*8> b4( static_cast<unsigned long>(y) ) ;
    std::bitset<sizeof(int)*8> b5( static_cast<unsigned long>(~y) ) ;
    std::bitset<sizeof(int)*8> b6( static_cast<unsigned long>(-~y) ) ;
    std::cout << y << " " << (~y) << " " << (-~y) << std::endl ;
    std::cout << b4 << "\n" << b5 << "\n" << b6 << std::endl ;
}