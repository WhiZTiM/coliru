#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>

int main()
{
   std::vector<char> data;
   
   std::copy(
      std::istream_iterator<char>(std::cin),
      std::istream_iterator<char>(),    // (this magic is like "end()" for streams)
      std::back_inserter(data)
   );
   
   std::cout << data.size() << '\n';
}
