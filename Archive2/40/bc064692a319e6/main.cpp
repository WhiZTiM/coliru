#include <map>
#include <sstream>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/unordered_set.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

int main()
{
  std::stringstream ss;
    
  std::unordered_map<int, std::unordered_set<int> > s, out;
  s.emplace( 0, std::unordered_set<int>{9,19} );
  boost::archive::text_oarchive oarch(ss);
  oarch << s;
  boost::archive::text_iarchive iarch(ss);
  iarch >> out;
  std::cout << (s == out) << std::endl;
}