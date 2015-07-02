// Please implement isPow2, such that it returns true if the argument is a power of 2, or false if it is not

#include <iostream>


bool isPow2( unsigned int num )

{
    int c=0;
    while(num>0)
    {
        c += (num&1);
        num>>=1;
    }
    
    return c==1;
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