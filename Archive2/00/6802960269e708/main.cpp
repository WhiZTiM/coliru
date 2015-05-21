
#include <iostream>
#include <vector>
#include <cassert>
#include <functional>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include <algorithm>

class A
{
};

class B :  public  A
{

};


int main()
{
    boost::sharep_ptr< B > p( new B);
    
    std::list< boost::shared_ptr<A> > array;
    array.push_back( p );
    /*
    std::string line(" bottom   right ");
    boost::trim(line);
    std::vector<std::string> strs;
    boost::split(strs,line,boost::is_any_of(" "),boost::token_compress_on);

    std::cout << "* size of the vector: " << strs.size() << std::endl;    
    for (size_t i = 0; i < strs.size(); i++) {
        std::cout << "|"<<strs[i]<< "|" << std::endl;
    }
    
    std::vector<float> F = {1, 2.2, 0 , 10.3};
    bool e = (F.end() != std::find_if(F.begin(), F.end(), boost::bind(std::less<float>(), _1, 0.0f) ) );
    std::cout << e << std::endl;
    std::vector<float> F1 = {1, 2.2, -0.5, 10.3};
    e = (F.end() != std::find_if(F1.begin(), F1.end(), boost::bind(std::less<float>(), _1, 0.0f) ) );
    std::cout << e << std::endl;
    std::vector<float> F2 = {1, 2.2, -1.1 , 10.3};
    e = (F2.end() != std::find_if(F2.begin(), F2.end(), boost::bind(std::less<float>(), _1, 0.0f) ) );
    std::cout << e << std::endl;
    std::vector<float> F3 = {1, 2.2, 0.5, 0.3};
    e = (F3.end() != std::find_if(F3.begin(), F3.end(), boost::bind(std::less<float>(), _1, 0.0f) ) );
    std::cout << e << std::endl;
    */
  //  std::vector<int> a = {1,2,3,4, 0, 5,6};    
    //bool e = (a.end() != std::find_if(a.begin(), a.end(), boost::bind(is_valid, _1) != 0 ) );
//    std::cout << e << std::endl;
    return 0;
}


