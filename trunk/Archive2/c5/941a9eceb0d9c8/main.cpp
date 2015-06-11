#include <iostream>
#include <utility>
#include <iterator>
#include <algorithm>


template<class Iterator>
struct range {
  Iterator b = {};
  Iterator e = {};
  Iterator begin() { return b; }
  Iterator end() { return e; }
  range(Iterator s, Iterator f):b(s),e(f) {}
  range()=default;
  explicit range(Iterator s, size_t n):b(s), e(s+n) {}
  decltype(auto) operator[](size_t N) { return b[N]; }
  decltype(auto) operator[] (size_t N) const { return b[N]; }\
  decltype(auto) front() { return *b; }
  decltype(auto) back() { return *std::prev(e); }
  bool empty() const { return begin()==end(); }
  size_t count() const { return end()-begin(); }
};

template<class T>
struct indexT
{
  T t = {};
  indexT()=default;
  indexT(T tin):t(tin){}
  indexT& operator++(){ ++t; return *this; }
  indexT operator++(int){ auto tmp = *this; ++t; return tmp; }
  T operator*()const{return t;}
  bool operator==( indexT const& o )const{ return t==o.t; }
  bool operator!=( indexT const& o )const{ return t!=o.t; }
  // etc if you want full functionality.
  // The above is enough for a `for(:)` range-loop
};

template<class ItA, class ItB>
struct indexing_iterator:indexT<ItA> {
  ItB b;
  // TODO: add the typedefs required for an iterator here
  // that are going to be different than indexT<ItA>, like value_type
  // and reference etc.  (for simple use, not needed)
  indexing_iterator(ItA a, ItB bin):indexT<ItA>(a), b(bin) {}
  indexT<ItA>& a() { return *this; }
  indexT<ItA> const& a() const { return *this; }
  decltype(auto) operator*() {
    return b[**a()];
  }
  decltype(auto) operator->() {
    return std::addressof(b[**a()]);
  }
};

template<class T>
using indexT_range = range<indexT<T>>;
using index = indexT<size_t>;
using index_range = range<index>;
index_range indexes( size_t start, size_t finish ) {
  return {index{start},index{finish}};
}
template<class C>
size_t size(C&&c){return c.size();}
template<class T, std::size_t N>
size_t size(T(&)[N]){return N;}

template<class C>
index_range indexes( C&& c ) {
  return indexes( 0, size(c) );
}
index_range intersect( index_range lhs, index_range rhs ) {
  if (lhs.b.t > rhs.e.t || rhs.b.t > lhs.b.t) return {};
  return {index{(std::max)(lhs.b.t, rhs.b.t)}, index{(std::min)(lhs.e.t, rhs.e.t)}};
}

template<class R, class It>
auto index_filter_it( R&& r, It it ) {
  using std::begin; using std::end;
  using ItA = decltype( begin(r) );
  using Ret = range<indexing_iterator<ItA, It>>;
  return Ret{{begin(r),it}, {end(r),it}};
}
template<class C>
auto index_filter( index_range r, C& c ) {
  r = intersect( r, indexes(c) );
  using std::begin;
  return index_filter_it( r, begin(c) );
}


int main() {
    int numbers[]={0,1,2,3,4,5,6,7,8,9};
    for (auto&& i : index_filter( indexes(0,6), numbers )) {
        std::cout << i << ',';
    }
    std::cout << "\n";
    for (auto&& i : index_filter_it( numbers, numbers )) {
        std::cout << i << ",";
    }
    std::cout << "!\n";
    std::vector<int> v={6,5,4,3,2};
    for (auto&& i : index_filter_it( v, numbers )) {
        std::cout << i << ",";
    }
    std::cout << "?\n";
}