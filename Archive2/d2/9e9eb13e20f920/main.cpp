// lower_bound example
#include <iostream>     // std::cout
#include <algorithm>    // std::lower_bound
#include <vector>       // std::vector

int main () {
  double myvalues[] = {10.0,20.0,30.0,35.0,22.0,11.0,13.0,26.0};
  std::vector<double> v(myvalues,myvalues+8);           // 10 20 30 30 22 11 13 26
  std::sort (v.begin(), v.end());                  // 10 11 13 20 22 26 30 35

  std::vector<double>::iterator low,up;
  
  double time = 35;
  
  low = std::lower_bound (v.begin(), v.end(), time); //          ^
  
  if (low != v.end())
  {
      std::cout << "First entry greater than or equal to "<< time << " is v[" << (low- v.begin()) << "] = "<< *low << '\n';
  }
  else
  {
      std::cout << "No entries this big.\n" << std::flush;
  }

  return 0;
}