#include <iostream>
#include <string>
#include <vector>


#include <boost/any.hpp>

auto stack = [](auto ...elems) { 
    return [=](auto op) { return op(elems...); }; 
};

auto concat = [](auto xs1, auto xs2) {
    auto op1 = [=](auto... p) {
      auto op2 = [=](auto... q) {
        return stack(p..., q...);
      };
      return xs2(op2);
    };
    return xs1(op1);
};

//auto constant = [](auto a) { return [&](auto next, auto ... stack) { return next (a, stack...);};};

auto top = [](auto xs) { 
    return xs([=](auto first, auto ... last) { return first; }); 
}; 

auto pop = [](auto xs) { 
    return xs([=](auto first, auto ... last) { return stack(last...); }); 
};

auto value = top;

auto add = [](auto xs) { 
    auto r = value(xs);
    auto bottom1 = pop(xs);
    auto l = value(bottom1);
    return concat (stack(l+r), pop(bottom1));
};


/*
auto compose = [](auto fun, auto token)
{
    if (token == std::string("+"))
    {
    }
    
    
    
    std::istringstream iss;
    
};
*/

auto print = [](auto a) { std::cout << a << std::endl;};

int main(int argc, char** argv)
{

/*auto fun = constant(argv[0]);
    
    for (int i = 0: i < argc; i++)
    {
        fun = compose(fun, argv[i]);
    }
  */

/*
  print (value(stack(1)));
  print (value(stack(2, 1)));
  print (value(add(stack(2, 1))));
  */

    auto s = stack();
    for (int i = 0; i < argc; i++)
    {
        auto token = argv[i];
        if (token == std::string("+"))
        {
            s = add(s);
        }
        else
        {
            s = concat (stack(atoi(token)), s);
        }
    }
    
    print (value(s));
    return 0;
}
