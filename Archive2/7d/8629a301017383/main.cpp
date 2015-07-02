#include <vector>
#include <string>
#include <iostream>
#include <cassert>


#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>

using namespace ranges;


namespace ranges {
template <class T, class U>
std::ostream& operator << (std::ostream& os, common_pair<T, U> const& p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
}

#define EXPECT_DOUBLE_EQ( x, y ) assert( x == y ) ;

int main() {
    std::array<double,4> ExpectedRadialDistortion = {{0.02557, 0.00624, 0.00674, -0.00171}} ;
    std::array<double,4> RadialDistortion = {{0.02557, 0.00624, 0.00674, -0.00171}} ;
    
     auto zipped = view::zip(ExpectedRadialDistortion, RadialDistortion);
  
  
  for( const auto & item : zipped )
  {
      std::cout << item.first << " " << item.second << std::endl ;
      EXPECT_DOUBLE_EQ( item.first, item.second ) ;
  }
  
}
