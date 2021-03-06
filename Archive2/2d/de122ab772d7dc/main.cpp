#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using std::cout;
using std::endl;

template <template <typename, typename...> class container_type> struct SortTraits {

  template <class comparator_type>
  static void sort(container_type<size_t> &front, comparator_type comp) {
    std::sort(front.begin(), front.end(), comp);
  }
};

//! Alias template used for the type of container used to store a front
template <class T> using container_template = std::list<T>;

template <> struct SortTraits<container_template> {

  template <class T, class comparator_type>
  static void sort(container_template<T> &front, comparator_type comp) {
    front.sort(comp);
  }
};

struct MyFunctor {
  bool operator()( const size_t& a, const size_t& b ) const {
    return a>b;
  }
};

int main() {

  //! Concrete type for a front
  typedef container_template<size_t> front_type;

  front_type myContainer = {3,5,2,6,3,6,7};

  MyFunctor mySortFunctor;

  SortTraits<container_template>::sort(myContainer, mySortFunctor);

  for (auto it = myContainer.begin(); it != myContainer.end(); ++it)
    cout<<" "<<*it;
  cout<<endl;
}