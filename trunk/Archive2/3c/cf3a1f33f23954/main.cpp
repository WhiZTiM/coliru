#include <bitset>
#include <string>
#include <iostream>
#include <climits>
#include <cmath>
 
int main() 
{
    // empty constructor
    std::bitset<20> b1(0); // [0,0,0,0,0,0,0,0]
 
    b1.set(0);
    b1.set(2);
    b1.set(3);
    b1.set(5);
    std::cout<<b1.all()<<std::endl;
    b1.set(1);
    b1.set(4);
    b1.set(6);
    b1.set(7);
    std::cout<<b1.all()<<"|"<<b1.size()<<std::endl;
    
    std::cout<<"Sizeof: "<<sizeof(b1)<<std::endl;
    
    // unsigned long long constructor
    std::bitset<8> b2(42);          // [0,0,1,0,1,0,1,0]
    std::bitset<70> bl(ULLONG_MAX); // [0,0,0,0,0,0,1,1,1,...,1,1,1] in C++11
    std::bitset<8> bs(0xfff0);      // [1,1,1,1,0,0,0,0]
 
    // string constructor
    std::string bit_string = "110010";
    std::bitset<8> b3(bit_string);       // [0,0,1,1,0,0,1,0]
    std::bitset<8> b4(bit_string, 2);    // [0,0,0,0,0,0,1,0]
    std::bitset<8> b5(bit_string, 2, 3); // [0,0,0,0,0,0,0,1]
 
    // string constructor using custom zero/one digits
    std::string alpha_bit_string = "aBaaBBaB";
    std::bitset<8> b6(alpha_bit_string, 0, alpha_bit_string.size(),
                      'a', 'B');         // [0,1,0,0,1,1,0,1]
 
    // char* constructor using custom digits
    std::bitset<8> b7("XXXXYYYY", 8, 'X', 'Y'); // [0,0,0,0,1,1,1,1]
 
    std::cout << b1 << '\n' << b2 << '\n' << bl << '\n' << bs << '\n'
              << b3 << '\n' << b4 << '\n' << b5 << '\n' << b6 << '\n'
              << b7 << '\n';
}