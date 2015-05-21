
#include <iostream>
#include <vector>
#include <cassert>
#include <functional>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

class A
{
};

class B :  public  A
{

};


int main()
{
    boost::shared_ptr< B > p1( new B );
    boost::shared_ptr< B > p2( new B );
    std::vector< boost::shared_ptr<A> > array;
    array.push_back( p1 );
    array.push_back( p2 );
    
    return 0;
}


