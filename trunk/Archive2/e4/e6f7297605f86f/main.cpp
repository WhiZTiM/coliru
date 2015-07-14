#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

auto func4(std::vector<double>& v) 
{
  return std::transform(v.begin(), v.end(), v.begin(),
                 [](double d) { return d < 0.00001 ? 0 : d; }
                 );
}


int main()
{
    std::vector<double> v {11.3, 34.3, 234.5, 0.0000001 };
    
    auto a = func4(v);
    
    std::cout << a;
    
}
