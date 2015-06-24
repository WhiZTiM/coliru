#include <boost/type_traits.hpp>
#include <iostream>
#include <string>
#include <functional>

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

class Guard final
{
public:
    Guard(std::function<void()> at_scope_exit)
    : f_(std::move(at_scope_exit))
    {
    }

    ~Guard() noexcept { try{ f_(); } catch(...) {} }
private:
    std::function<void()> f_;
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
    
    auto t = [](std::string a) { return a.size();  };

   
    std::function<int(std::string)> s = [](std::string a) { return 5;  };   
    RAIIFunc<int (std::string), close2 > f = open2(3,4);
    
    
    
    
    return 0;    
}