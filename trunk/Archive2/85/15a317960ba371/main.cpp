#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template <typename Container>
struct __pforeach__helper {
    Container &&c;
    template <typename Arg>
    void operator=(Arg&& arg) {
        parallel_for_each(std::forward<Container>(c), std::forward<Arg>(arg));
    }
};

//additional helper function
template <typename Container>
__pforeach__helper<Container> __create__pforeach__helper(Container &&c)
{
    return __pforeach__helper<Container>(__pforeach__helper<Container>{c});
}

#define pforeach(Z,C) \
  __create__pforeach__helper(C)=[](Z)
  

template <typename Container, typename Task>
void parallel_for_each(Container &&container, const Task &task)
{
    std::for_each(std::begin(container), std::end(container), task);
}

int main()
{
    std::vector<double> vec;
    vec.resize(5000, 5.23);
    
    pforeach(double &el, vec)
    {
        el*=2;
    };
    
    std::cout<<vec[0];
}
