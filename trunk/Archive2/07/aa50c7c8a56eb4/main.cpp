#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>

template <typename Container>
typename Container::value_type findSmallestNonunique(Container c)
{
   std::sort(std::begin(c), std::end(c));
   auto it = std::adjacent_find(std::begin(c), std::end(c));
   
   if (it == std::end(c))
      throw std::runtime_error("No such element found");
   
   return *it;
}

int main(int argc, char** argv)
{
    std::vector<int> v;
    for (int i = 1; i < argc; i++)
        v.push_back(std::stoi(argv[i]));
    
    std::cout << findSmallestNonunique(v) << std::endl;
}