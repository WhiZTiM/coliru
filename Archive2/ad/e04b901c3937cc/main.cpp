#include <iostream>
#include <boost/variant/variant.hpp>
#include <boost/variant/recursive_wrapper.hpp>

struct node;

typedef boost::variant<
    boost::recursive_wrapper<node>,
    int
    > expression;
    
struct node
{
    expression left;
    expression right;
};

int main()
{
    node n;
    std::cout << "finished\n";
    return 0;
}
