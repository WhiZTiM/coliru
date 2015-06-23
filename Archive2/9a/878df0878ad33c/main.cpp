#include <iostream>
#include <type_traits>
#include <utility>
#include <array>
#include <string>

template<class T>
struct array_view {
  T* b = 0;
  T* e = 0;
  T* begin()const{return b;}
  T* end()const{return e;}

  // defaults:
  array_view()=default;
  array_view(array_view const&)=default;
  array_view& operator=(array_view const&)=default;
  ~array_view()=default;

  array_view( T* s, size_t n ):array_view(s, s+n){}
  array_view( T* s, T* f ):b(s),e(f){}

  using mutable_T = typename std::remove_const<T>::type;

  template<size_t N>
  array_view( T(&arr)[N] ):array_view(arr, N){}
  template<size_t N>
  array_view( std::array<T,N>&arr ):array_view(arr.data(), N){}
  template<size_t N>
  array_view( std::array<mutable_T,N>const&arr ):array_view(arr.data(), N){}

  // similar for std::vector:
  template<class...Ts>
  array_view( std::basic_string<mutable_T, Ts...> const& src):
    array_view(src.data(), src.size())
  {}
  template<class...Ts>
  array_view( std::basic_string<T, Ts...>& src):
    array_view(
      src.empty()?
        array_view():
        array_view(std::addressof(src[0]),src.size())
    )
  {}

  T& back() const { return *std::prev(end()); }
  T& front() const { return *begin(); }
  size_t size() const { return end()-begin(); }
  bool empty() const { return begin()==end(); }

  // slicing functions:
  array_view front( size_t n ) const {
    if (size() <= n) return *this;
    return {begin(), n};
  }
  array_view back( size_t n ) const {
    if (size() <= n) return *this;
    return {end()-n, n};
  }
  array_view trim_front( size_t n ) const {
    return back( size()-n );
  }
  array_view trim_back( size_t n ) const {
    return front( size()-n );
  }
  array_view sub( size_t start, size_t len ) const {
    if (start >= size()) return {};
    len = (std::min)( size()-start, len );
    return {begin()+start, len};
  }

  // comparisons:
  friend bool operator==( array_view lhs, array_view rhs ) {
    if (lhs.size()!=rhs.size()) return false;
    return std::equal( lhs.begin(), lhs.end(), rhs.begin() );
  }
  friend bool operator!=( array_view lhs, array_view rhs ) {
    return !(lhs==rhs);
  }
  friend bool operator<( array_view lhs, array_view rhs ) {
    return std::lexicographical_compare(
      lhs.begin(), lhs.end(),
      rhs.begin(), rhs.end()
    );
  }
  friend bool operator>( array_view lhs, array_view rhs ) {
    return rhs<lhs;
  }
  friend bool operator<=( array_view lhs, array_view rhs ) {
    return !(lhs>rhs);
  }
  friend bool operator>=( array_view lhs, array_view rhs ) {
    return !(lhs<rhs);
  }
};

using string_view = array_view<const char>;

size_t common_prefix( string_view lhs, string_view rhs ) {
  auto itl = lhs.begin();
  auto itr = rhs.begin();
  while (itl != lhs.end() && itr != rhs.end()) {
    if (*itl != *itr) break;
    ++itl; ++itr;
  }
  return itl-lhs.begin();
}

bool is_yz_zy( string_view lhs, string_view rhs ) {
  if (lhs.size() <= 2) return false;
  if (lhs.size() != rhs.size()) return false;
  for (size_t i = 1; i < (lhs.size()-1); ++i) {
    if (lhs.front(i)==rhs.back(i)) {
      if (lhs.trim_front(i) == rhs.trim_back(i)) {
        return true;
      }
    }
  }
  return false;
}

bool is_xyz_xzy( string_view lhs, string_view rhs ) {
  size_t max_x = common_prefix(lhs, rhs);
  for (size_t i = 1; i < max_x; ++i) {
    if (is_yz_zy( lhs.trim_front(i), rhs.trim_front(i) ))
      return true;
  }
  return false;
}

int main()
{
    std::string lhs = "abcbd";
    std::string rhs = "abdbc";
    std::cout << is_xyz_xzy( lhs, rhs ) << "\n";
    lhs = "abcdx";
    std::cout << is_xyz_xzy( lhs, rhs ) << "\n";

}