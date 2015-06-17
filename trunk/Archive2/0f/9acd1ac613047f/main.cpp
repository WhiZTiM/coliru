#include <boost/type_traits.hpp>
#include <iostream>
#include <string>

template<typename FuncType, FuncType * Func>
class RAIIFunc
{
public:
   typedef typename boost::function_traits<FuncType>::arg1_type arg_type;
   RAIIFunc(arg_type p) : p_(p) {}
   ~RAIIFunc() { Func(p_); }
   arg_type & getValue() { return p_; }
   arg_type const & getValue() const { return p_; }
private:
   arg_type p_;
};


std::string open2(int n,int m)
{
    std::cout<<"open: "<<n<<"\n";   
    return "Hello";
}

int close2(std::string n)
{
    std::cout<<"close: "<<n<<"\n";
    return 2;
}

int main() {
    
    RAIIFunc<int (std::string), close2> f = open2(3,4);
    
    
    return 0;    
}