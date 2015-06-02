#include <boost/scope_exit.hpp>

int main() {
    auto i = new int;
    BOOST_SCOPE_EXIT_ALL(&) { delete i; };    
}