#include <iostream>
//#include <cstdint>

int main()
{
   float f (1.27007f);
   int ff = *reinterpret_cast<int*>(&f);
   std::cout << std::hex
             << ((ff >> 24) & 0xff) << " "
             << ((ff >> 16) & 0xff) << " "
             << ((ff >> 8) & 0xff) << " "
             << (ff & 0xff)
      << std::endl;  
            
   double d = f;       
   long long dd = *reinterpret_cast<long long*>(&d);
   std::cout << std::hex
             << ((dd >> 56) & 0xff) << " "
             << ((dd >> 48) & 0xff) << " "
             << ((dd >> 40) & 0xff) << " "
             << ((dd >> 32) & 0xff) << " "
             << ((dd >> 24) & 0xff) << " "
             << ((dd >> 16) & 0xff) << " "
             << ((dd >> 8) & 0xff) << " "
             << (dd & 0xff)
             << std::endl;   
    
    double t (1.27007);
    long long tt = *reinterpret_cast<long long*>(&t);
   std::cout << std::hex
             << ((tt >> 56) & 0xff) << " "
             << ((tt >> 48) & 0xff) << " "
             << ((tt >> 40) & 0xff) << " "
             << ((tt >> 32) & 0xff) << " "
             << ((tt >> 24) & 0xff) << " "
             << ((tt >> 16) & 0xff) << " "
             << ((tt >> 8) & 0xff) << " "
             << (tt & 0xff);   
    
    std::cout.precision(62);
    std::cout << std::endl << d << std::endl << f << std::endl << t;
      
}