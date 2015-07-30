#include <iostream>


bool isPow2( unsigned int num )

{
    
 while (((num % 2) == 0) && num > 1) 
   num /= 2;
 return (num == 1);
}


int main( int argc, char** argv )

{

  const unsigned int test_number = 12;


   if( isPow2( test_number ) )

   {

      std::cout << test_number << " is a power of 2" << std::endl;

   }

   else

   {

      std::cout << test_number << " is NOT a power of 2" << std::endl;

   }

}