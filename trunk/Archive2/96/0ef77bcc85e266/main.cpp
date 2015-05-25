#include <boost/multi_index_container.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <cassert>
#include <set>

template<typename T>
using set_set=boost::multi_index_container<
  std::set<T>,
  boost::multi_index::indexed_by<
    boost::multi_index::ordered_unique<
      boost::multi_index::identity<std::set<T>>
    >
  >
>;

int main()
{
  set_set<int> ss={{0,1,2},{1,2,3},{2,3,4},{6,4,5}};
  
  auto it=ss.find(std::set<int>{6,4,5}); // get last element
  ss.modify(it,[](auto& s){
    s.erase(6);   // change 6
    s.insert(3);  // for 3
  });
  assert((*it==std::set<int>{3,4,5}));
}
