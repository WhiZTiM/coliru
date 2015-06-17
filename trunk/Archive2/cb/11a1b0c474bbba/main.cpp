#include <iostream>
#include <vector>

#include <boost/iterator/zip_iterator.hpp>

typedef boost::tuple<int&, float&> EntryTuple;

struct zip_func :
  public std::unary_function<EntryTuple&, void>
{
  void operator()(EntryTuple& t) const
  {
    std::cout << t.get<0>() << " " <<  t.get<1>() << std::endl;
  }
};


int main()
{

const int N = 5;
std::vector<int> intVec(N,2);
std::vector<float> valueVec(N,5.5);

std::for_each(
boost::make_zip_iterator(
  boost::make_tuple(intVec.begin(), valueVec.begin())
  ),
boost::make_zip_iterator(
  boost::make_tuple(intVec.end(), valueVec.end())
  ),
zip_func()
);

return 0;
}