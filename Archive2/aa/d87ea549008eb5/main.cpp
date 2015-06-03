// Please implement isPow2, such that it returns true if the argument is a power of 2, or false if it is not
 
#include <iostream>
 



bool isPow2( unsigned int num )
 
{
    bool res = 0;
    int i;

    if (num == 0)
	{
		return false;
	}

	while (num != 1)
	{
		i = num % 2;
		if (i != 0)
		{
			return false;
		}
		else
		{
			num = num / 2;
		}
	}
	return true;
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
