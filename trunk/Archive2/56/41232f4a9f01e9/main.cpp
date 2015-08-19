#include <iostream>
#include <vector>
#include <string>

struct character { int room ; character( int r = 0 ) : room(r) {} };

void pass_by_value( std::vector<character> players )
{ for( character& c : players ) c.room = 99 ;  }

void pass_by_reference( std::vector<character>& players )
{ for( character& c : players ) c.room = 99 ;  }

std::vector<character> pass_by_value_return_modified_object( std::vector<character> players )
{
    for( character& c : players ) c.room = 99 ;
    return players ;
}

void print( const std::vector<character>& players )
{
    for( character c : players ) std::cout << c.room << ' ' ;
    std::cout << '\n' ;
}

int main()
{
    {
        std::cout << "------  pass by value ------\n" ;
        std::vector<character> players { 0, 1, 2, 3, 4, 5 } ;
        print(players) ;
        pass_by_value(players) ;
        print(players) ;
    }


    {
        std::cout << "\n------  pass by reference ------\n" ;
        std::vector<character> players { 0, 1, 2, 3, 4, 5 } ;
        print(players) ;
        pass_by_reference(players) ;
        print(players) ;
    }

    {
        std::cout << "\n------  pass by pass by value, return_modified_object------\n" ;
        std::vector<character> players { 0, 1, 2, 3, 4, 5 } ;
        print(players) ;

        std::cout << "ignore the result: " ;
        pass_by_value_return_modified_object(players) ; // ignore the result
        print(players) ;

        std::cout << "update object with the result: " ;
        players = pass_by_value_return_modified_object(players) ; // update object with the result
        print(players) ;
    }
}
