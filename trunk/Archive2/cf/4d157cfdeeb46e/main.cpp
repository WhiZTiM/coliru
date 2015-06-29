#include <algorithm>
#include <array>
#include <iostream>

int main()
{
  int arr[] {1,2,3,4,5};
  std::cout << std::accumulate(std::begin(arr), std::end(arr), 0);
}
