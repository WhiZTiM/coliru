#include <vector>
#include <iostream>

int main( ) {
   const int ASIZE = 5;
   char arraybefore[ASIZE] = { 'h', 'e', 'l', 'l', 'o' };
   char array[ASIZE] = { 'a', 'b', 'c', 'd', 'e' };
   char arrayAfter[ASIZE] = { 'h', 'e', 'l', 'l', 'o' };

   //const char * var1 = array;
   std::vector<char> var2 ( array, array + 7 );
   for ( auto cIt : var2 ) {
      std::cout << cIt << " ";
   }
   std::cout << std::endl << arraybefore[1] << arrayAfter[1];
   std::cout << std::endl << "done" << std::endl;
}