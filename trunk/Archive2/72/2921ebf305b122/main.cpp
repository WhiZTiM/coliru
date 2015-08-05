#include <iostream>

int main ()
{
  int firstvalue = 25 ;
  int secondvalue = 15;
  int* p1 = std::addressof(firstvalue) ;
  int* p2 = std::addressof(secondvalue) ;

const auto points_to = [&] ( const int* pointer ) 
{ 
    if( pointer == std::addressof(firstvalue) ) return " (points to firstvalue)" ; 
    else if( pointer == std::addressof(secondvalue) ) return " (points to secondvalue)" ;
    else return "" ;
};

const auto dump = [&] ( const char* desc )
  {
      std::cout << desc << "\n------------------\n"
                << " firstvalue: has address " << std::addressof(firstvalue) << " value " << firstvalue << '\n'
                << "secondvalue: has address " << std::addressof(secondvalue) << " value " << secondvalue << '\n'
                << "         p1:   points to " << p1 << " value " << *p1 << points_to(p1) << '\n'
                << "         p2:   points to " << p2 << " value " << *p2 << points_to(p2) << "\n\n" ;
  };

  dump( "after initialisation") ;
  *p1 = 10; dump( "after *p1 = 10" ) ;
  *p2 = *p1;  dump( "after *p2 = *p1" ) ;
  p1 = p2;  dump( "after p1 = p2" ) ;
  *p1 = 20; dump( "after *p1 = 20" ) ;
}
