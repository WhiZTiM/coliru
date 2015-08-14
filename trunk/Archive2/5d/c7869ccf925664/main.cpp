#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <functional>
#include <sstream>
#include <type_traits>

    std::string identity( std::string in ) { return std::move(in); }
    
    template<class F>
    struct interacter_t {
      F f;
      void operator()( std::istream& is = std::cin, std::ostream& os = std::cout ) {
        std::string in;
        while( getline( is, in ) ) {
          os << f(std::move(in)) << '\n';
        }
      }
    };
    template<class F>
    interacter_t<std::decay_t<F>> interact( F&& f ) {
      return {std::forward<F>(f)};
    }

    int main() {
      auto io = interact(identity);
      std::cout << "Start:\n";
      io();
      std::cout << "End.\n";
    }
    
