#include <algorithm>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>

int main()
{
    std::vector<int> from_vector(10);
//    for (int i = 0; i < 10; i++) {
//        from_vector.push_back(i);
//    }
    std::iota(from_vector.begin(), from_vector.end(), 0);
 
    std::vector<int> to_vector(15);
 
    std::copy_backward(from_vector.begin(), from_vector.end(), to_vector.end());
 
//    std::cout << "to_vector contains: ";
//    for (unsigned int i = 0; i < to_vector.size(); i++) {
//        std::cout << to_vector[i] << " ";
//    }

      std::copy(to_vector.begin(), to_vector.end(),
              std::ostream_iterator<int>(std::cout, " "));
      std::cout << '\n';
 }