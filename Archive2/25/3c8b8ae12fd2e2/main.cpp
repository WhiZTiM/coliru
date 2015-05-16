#include <boost/any.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <string>

namespace fus = boost::fusion;

class container
{
  protected:
    boost::any children;

    template <typename T>
    container (T const& children) : children(children) {}
};

class derived : public container
{
    using V = boost::fusion::vector2<std::string, std::string>;
  public:
    derived() : 
        container(fus::make_vector(std::string("test1"),std::string("test"))){} 

    friend std::ostream& operator<<(std::ostream& os, derived const& d) {
        return os << boost::any_cast<V const&>(d.children);
    }
};

#include <iostream>

int main() {
    derived d;
    std::cout << d;
}
