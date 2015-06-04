#include <iostream>
#include <utility>
#include <boost/lexical_cast.hpp>

namespace my
{
   struct my_pair : std::pair<int, int> {};
   
   std::istream& operator>>(std::istream& stream, my_pair& pair)
   {
      stream >> pair.first;
      stream >> std::skipws;
      stream >> pair.second;
      return stream;
   }
}

int main()
{
    my::my_pair p = boost::lexical_cast<my::my_pair>("10 10");
    std::cout << p.first << " " << p.second << std::endl;
}