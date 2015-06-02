#include <iostream>
#include <set>
#include <vector>


void isSubgroup(  std::set<std::string>& group, 
                 const std::vector<std::string>& subgroups )
{
    std::vector<std::string>::const_iterator i = subgroups.begin() ;

    std::pair<std::set<std::string>::iterator,bool> p;

    for( ; i != subgroups.end(); ++i )
    {
        p = group.insert( *i );
        if( p.second ) // Present in group
        {
                 break;
        }
    }
    
    if( i == subgroups.end() )
        std::cout << std::boolalpha << true << std::endl;
    else
        std::cout << std::boolalpha << false << std::endl;
        
}

int main()
{
    


std::set<std::string> group1 {"A","B","C","D"} ;// C++11 Just for initilization
std::vector<std::string> subgroups1  = {"A","D","E"} ; // C++11 Just for initilization

isSubgroup( group1, subgroups1 ) ;

std::set<std::string> group2 {"A","B","C","D"} ;
std::vector<std::string> subgroups2  = {"A","D"} ;
isSubgroup( group2, subgroups2 ) ;
}
