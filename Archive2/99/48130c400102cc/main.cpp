// Vector.h
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

template<typename T> class Vector;
template<typename T> std::ostream& operator<< ( std::ostream& s, const Vector<T>& other );

template<typename T>
class Vector {
  std::vector<T> base;

  // vector + scalar
  template<typename T1, typename T2>
  friend auto operator+(const Vector<T1> & lhs, const T2 & scalar) -> Vector<std::common_type_t<T1,T2>>;         

  friend std::ostream& operator<< <T> ( std::ostream& s, const Vector<T>& other );

public:
  Vector();
  Vector( const Vector<T>& other );
  Vector<T>& operator= ( const Vector<T> &other );
  auto& operator[] ( int i );
  void insert( const T element );
};

template<typename T>
Vector<T>::Vector() {
}

template<typename T>
Vector<T>::Vector( const Vector<T>& other ) {
  base = other.base;
}

template<typename T>
Vector<T>& Vector<T>::operator= ( const Vector<T> &other ) {
  base = other.base;
}

template<typename T>
auto& Vector<T>::operator[] ( int i ) {
  assert( i >= 0 && i < base.size() );
  return base[i];
}

template<typename T>
void Vector<T>::insert( const T element ) {
  base.push_back( element );
}

// vector + scalar
template<typename T1, typename T2>
auto operator+(const Vector<T1> & lhs, const T2 & scalar)
  -> Vector<std::common_type_t<T1,T2>>
{
  using T3 = std::common_type_t<T1,T2>;
  Vector<T3> result;
  result.base.reserve(lhs.base.size());
  std::transform(lhs.base.begin(), lhs.base.end(), std::back_inserter(result.base),
                 [&scalar](const T1 & element) { return element + scalar; });
  return result;
}

// vector_test.cpp

void test_vector_int_scalar_int_addition() {
  Vector<int> v;
  v.insert( 1 );
  v.insert( 2 );
  v.insert( 3 );
  int s = 2;
  Vector<int> res = v + s;
  }

void test_vector_short_scalar_short_addition() {
   Vector<short> v;
   v.insert( 1 );
   v.insert( 2 );
   v.insert( 3 );
   short s = 2;
   Vector<short> res = v + s;
}

int main() {
   test_vector_int_scalar_int_addition(); // Compiles and works
   test_vector_short_scalar_short_addition(); // Does NOT compile
}
