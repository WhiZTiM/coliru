#include <iostream>
#include <iterator>
#include <vector>

template <class T, int N>
std::vector<T> vector_from_array(const T (&array)[N]) {
  return std::vector<T>(array, array + N);
}

int main()
{
  const double a[] = {1., 2., 3., 4., 5.};
  std::vector<double> a_vec = vector_from_array(a);
  std::copy(a_vec.begin(), a_vec.end(), std::ostream_iterator<double>(std::cout, " "));
  std::cout << "\n";
  
  return 0;
}