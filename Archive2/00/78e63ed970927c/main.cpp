#include <iostream>


namespace compile_time
{
    auto stack = [](auto ...elems) { 
        return [=](auto op) { return op(elems...); }; 
    };
    
    auto cat = [](auto elem) {
        return [=](auto ...elems) { return stack(elem, elems...); };
    };
    
    auto add = [](auto a, auto b, auto... elems) { 
        return stack(a+b, elems...);
    };
    
    auto value = [](auto first, auto ... rest) { 
        return first;
    };
}

#include <stack>
#include <vector>
//#include <boost/any.hpp>

namespace run_time
{
    constexpr struct value_t {} value{};
    
    struct stack_t
    {                
        using data_t = std::stack<int, std::vector<int>>;
        using value_type = typename data_t::value_type;
        
        value_type pop()
        {
            auto res = data_m.top();
            data_m.pop();
            return res;
        }

        void push(value_type v)
        {
            data_m.emplace(std::move(v));
        }

        template <typename Op>
        stack_t & operator()(Op op)
        {
            op(*this);
            return *this;
        }
        
        value_type operator() (value_t)
        {
            return pop();
        }

    private:
        data_t data_m;
    };
    
    stack_t stack () { return stack_t{};};
    
    auto cat = [](auto elem) {
        return [=](auto& s) { s.push(elem); };
    };
    
    auto add = [](auto& s) {
        auto r = s.pop();
        auto l = s.pop();
        s.push(l + r);
    };
}

auto print = [](auto elem) {
    std::cout << elem << std::endl;
};

int main(int argc, char** argv)
{
    {
        using namespace compile_time;
        
        print(stack(1u)(cat(2))(value));
        print(stack()(cat(1))(value));
        print(stack()(cat(1))(cat(2))(value));
        print(stack()(cat(1))(cat(2))(add)(value));
        print(stack()(cat(1))(cat(2))(add)(cat(5))(add)(value));
    }

    {
        using namespace run_time;
        
        //print(stack(1u)(cat(2))(value));
        print(stack()(cat(1))(value));
        print(stack()(cat(1))(cat(2))(value));
        print(stack()(cat(1))(cat(2))(add)(value));
        print(stack()(cat(1))(cat(2))(add)(cat(5))(add)(value));
    }
/*
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
*/    
    return 0;
}
