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
             << (dd & 0xff);   
             
    std::cout << std::endl << d << std::endl << f;
      
}