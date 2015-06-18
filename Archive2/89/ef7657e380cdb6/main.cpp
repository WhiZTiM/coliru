#include <iostream>
#include <string>
#include <sstream>

int main()
{
   std::string test_str ;
   for( int i = 0 ; i < 3 ; ++i )
   {
       auto n = std::to_string(i+1) ;
       test_str += n + ". This is line #" + n + '\n' ;
   }

   {
       std::istringstream stm(test_str) ;

       std::string line ;
       int line_count = 0 ;

       std::cout << "-----  bad  -----\n" << stm.str() << "----------------\n" ;
       // while(good) is bad: it check for input failure *before* the attempted input
       while( stm.good() )  // ****
       {
           std::getline( stm, line ) ;
           ++line_count ;
       }
       std::cout << line_count << " lines were read\n" ;
   }

   {
       std::istringstream stm(test_str) ;

       std::string line ;
       int line_count = 0 ;

       std::cout << "\n-----  good  -----\n" << stm.str() << "----------------\n" ;
       // good: check for input failure *after* the attempted input
       while( std::getline( stm, line ) ) // ****
       {
           ++line_count ;
       }
       std::cout << line_count << " lines were read\n" ;
   }
}
