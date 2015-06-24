#include <iostream>
#include <type_traits>
#include <utility>
#include <array>
#include <string>

#define DEBUG(...)
// #define DEBUG(...) __VA_ARGS__

size_t char_compared = 0;

template<class T>
struct array_view {
  T* b = 0;
  T* e = 0;
  T* begin()const{return b;}
  T* end()const{return e;}

  T& operator[](size_t i)const{return b[i];}
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
    char_compared += lhs.size(); // or less
    return std::equal( lhs.begin(), lhs.end(), rhs.begin() );
  }
  friend bool operator!=( array_view lhs, array_view rhs ) {
    return !(lhs==rhs);
  }
  friend bool operator<( array_view lhs, array_view rhs ) {
    char_compared += (std::min)(lhs.size(), rhs.size()); // or less
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
  
  friend std::ostream& operator<<( std::ostream& os, array_view v ) {
      for (auto&& x:v) {
          os << x;
      }
      return os;
  }
};

using string_view = array_view<char>;

size_t common_prefix( string_view lhs, string_view rhs ) {
  auto itl = lhs.begin();
  auto itr = rhs.begin();
  while (itl != lhs.end() && itr != rhs.end()) {
    ++char_compared;
    if (*itl != *itr) break;
    ++itl; ++itr;
  }
  return itl-lhs.begin();
}

void inplace_scan( string_view s, char acc=0 )
{
    for (char& x:s) {
        ++char_compared;
        acc = acc^x;
        x = acc;
    }
}

void inplace_unscan( string_view s, char prev = 0 ) {
    for (char& x:s) {
        ++char_compared;
        std::swap(x,prev);
        x ^= prev;
    }
}

struct scan_mode:string_view {
    char prev;
    scan_mode( string_view in, char init=0 ):
        string_view(in),prev(init)
    {
        DEBUG(std::string tmp(begin(), end());)
        inplace_scan(*this, prev);
        DEBUG(inplace_unscan(*this, prev);
        if (tmp != *this)
            std::cout << tmp << "!=" << *this << "\n";
        inplace_scan(*this, prev);)
    }
    ~scan_mode() {
        inplace_unscan(*this, prev);
    }
};
struct unscan_mode:string_view {
    char prev;
    unscan_mode( string_view in, char init=0 ):
        string_view(in),prev(init)
    {
        inplace_unscan(*this, prev);
    }
    ~unscan_mode() {
        inplace_scan(*this, prev);
    }
};

bool is_yz_zy( string_view lhs_in, string_view rhs_in ) {
  if (lhs_in.size() < 2) return false;
  if (lhs_in.size() != rhs_in.size()) return false;
  
  scan_mode lhs = lhs_in;
  scan_mode rhs = rhs_in;
  
  for (size_t i = 1; i < lhs.size(); ++i) {
      ++char_compared;
      if (lhs[i-1] != (rhs[rhs.size()-1-i]^rhs.back())) {
          DEBUG(std::cout << std::hex << "0x"<< (int)lhs[i-1] <<"!= (0x"<< (int)rhs[rhs.size()-1-i] << "^0x"<< (int)rhs.back()<<") aka 0x" << int(rhs[rhs.size()-1-i]^rhs.back()) <<"\n";)
          continue;
      }
      unscan_mode lhs_yz = lhs;
      unscan_mode rhs_zy = rhs;
      string_view lhs_y = lhs_yz.front(i);
      string_view rhs_y = rhs_zy.back(i);
      
      if (lhs_y != rhs_y) {
        DEBUG(std::cout << lhs_y << "!=" << rhs_y << " (y)\n";)
        continue;
      }
      string_view lhs_z = lhs_yz.trim_front(i);
      string_view rhs_z = rhs_zy.trim_back(i);
      
      if (lhs_z != rhs_z) {
        DEBUG(std::cout << lhs_z << "!=" << rhs_z << " (z)\n";)
        continue;
      }
      return true;
  }
  return false;
}

bool is_xyz_xzy( string_view lhs, string_view rhs ) {
  size_t max_x = common_prefix(lhs, rhs);
  for (size_t i = 0; i <= max_x; ++i) {
    DEBUG(std::cout << "|x| = " << i << "\n";)
    if (is_yz_zy( lhs.trim_front(i), rhs.trim_front(i) ))
      return true;
  }
  return false;
}

int main()
{
    std::string lhs = "abcbd";
    std::string rhs = "abdbc";
    std::cout << is_xyz_xzy( lhs, rhs ) << " in " << char_compared << " steps vs "<< lhs.size() << " length\n";
    lhs = "abcdx";
    char_compared = 0;
    std::cout << is_xyz_xzy( lhs, rhs ) << " in " << char_compared << " steps vs "<< lhs.size() << " length\n";
    lhs = "kkkeeettt";
    rhs = "kkkttteee";
    char_compared = 0;
    std::cout << is_xyz_xzy( lhs, rhs ) << " in " << char_compared << " steps vs "<< lhs.size() << " length\n";
    lhs = "this is a really long sentence, what will we do.   !aaaaadsfsafdadsfdsafaaaaaaaaaaaaaaaaaaaafddsaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaxaaaaaaaaaaaaaaa";
    rhs = "this is a really long sentence, what will we do.   aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaxaaaaaaaaaaaaaaa!aaaaadsfsafdadsfdsafaaaaaaaaaaaaaaaaaaaafddsaaaaaaaaaaaaaaaa";
    char_compared = 0;
    std::cout << is_xyz_xzy( lhs, rhs ) << " in " << char_compared << " steps vs "<< lhs.size() << " length\n";
}