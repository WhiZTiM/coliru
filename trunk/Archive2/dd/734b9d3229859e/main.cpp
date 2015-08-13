#include <utility>      // std::pair
#include <iostream>     // std::cout
#include <vector>
#include <algorithm>

typedef std::pair<double, double> my_pair;
struct sort_pred
{
    bool operator () (const my_pair& lhs, const my_pair& rhs)
    {
        return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second>rhs.second);
    }
};

int main () {
      std::vector<my_pair> data;
      data.push_back(my_pair(3,2) );
      data.push_back(my_pair(1,2) );
      data.push_back(my_pair(1,1) );
      data.push_back(my_pair(2,2) );

      for(auto a: data)
            std::cout << "first "<< a.first << "  second " << a.second << std::endl;

      std::cout << "==========================\n";
      std::sort(data.begin(), data.end(), sort_pred());  
      for(auto a: data)
            std::cout << "first "<< a.first << "  second " << a.second << std::endl;

      return 0;
}