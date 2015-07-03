#include <string>
#include <iostream>
#include <boost/preprocessor.hpp>
#include <boost/lexical_cast.hpp>

#define ipar(x) p<int>(BOOST_PP_STRINGIZE(x))

template <typename T>
T p(std::string str) {
  return boost::lexical_cast<T>(str);
}

int main() {
  std::cout<<ipar(1)<<"\n";
}