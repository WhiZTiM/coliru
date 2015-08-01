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
  
  // scalar + vector
  template<typename T1, typename T2>
  friend auto operator+(const T1 & scalar, const Vector<T2> & rhs) -> Vector<std::common_type_t<T1,T2>>;
  
  // vector + vector
  template<typename T1, typename T2>
  friend auto operator+(const Vector<T1> & lhs, const Vector<T2> & rhs) -> Vector<std::common_type_t<T1,T2>>;

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

// scalar + vector
template<typename T1, typename T2>
  auto operator+(const T1 & scalar, const Vector<T2> & rhs)
  -> Vector<std::common_type_t<T1,T2>>
{
  using T3 = std::common_type_t<T1, T2>;
  Vector<T3> result;
  result.base.reserve(rhs.base.size());
  std::transform(rhs.base.begin(), rhs.base.end(), std::back_inserter(result.base),
                 [&scalar](const T2 & element) { return scalar + element; });
  return result;
}

// vector + vector
template<typename T1, typename T2>
  auto operator+(const Vector<T1> & lhs, const Vector<T2> & rhs)
    -> Vector<std::common_type_t<T1,T2>>
{
  using T3 = std::common_type_t<T1, T2>;
  assert(lhs.base.size() == rhs.base.size());
  Vector<T3> result;
  result.base.reserve(lhs.base.size());
  std::transform(lhs.base.begin(), lhs.base.end(), rhs.base.begin(), std::back_inserter(result.base),
                 [](const T1 & e1, const T2 & e2) { return e1 + e2; });
  return result;
}

template<typename T>
std::ostream& operator<< ( std::ostream& s, const Vector<T>& other ) {
  s << "(";
  size_t i;
  for ( i = 0; i < other.base.size() - 1; i++ ) {
    s << other.base[i] << ", ";
  }
  s << other.base[other.base.size() - 1] << ")";
  return s;
}

// vector_test.cpp

// vector + scalar (vector int and scalar int)
void test_vector_int_scalar_int_addition() {
  // Create vector
  Vector<int> v;
  v.insert( 1 );
  v.insert( 2 );
  v.insert( 3 );
  // Create scalar
  int s = 2;
  // vector * scalar
  Vector<int> res = v + s;
  std::cout << "res = v + s = " << v << " + " << s << " = " << res << std::endl;
}

// vector + scalar (vector float and scalar float)
void test_vector_float_scalar_float_addition() {
  // Create vector
  Vector<float> v;
  v.insert( 1.1 );
  v.insert( 2.1 );
  v.insert( 3.1 );
  // Create scalar
  float s = 2.1;
  // vector + scalar
  Vector<float> res = v + s;
  std::cout << "res = v + s = " << v << " + " << s << " = " << res << std::endl;
}

// vector + scalar (vector double and scalar double)
void test_vector_double_scalar_double_addition() {
  // Create vector
  Vector<double> v;
  v.insert( 1.1 );
  v.insert( 2.1 );
  v.insert( 3.1 );
  // Create scalar
  double s = 2.1;
  // vector + scalar
  Vector<double> res = v + s;
  std::cout << "res = v + s = " << v << " + " << s << " = " << res << std::endl;
}

// vector + scalar (vector short and scalar short)
void test_vector_short_scalar_short_addition() {
  // Create vector
  Vector<short> v;
  v.insert( 1 );
  v.insert( 2 );
  v.insert( 3 );
  // Create scalar
  short s = 2;
  // vector + scalar
  Vector<short> res = v + s;
  std::cout << "res = v + s = " << v << " + " << s << " = " << res << std::endl;
}

// vector + scalar (vector long and scalar long)
void test_vector_long_scalar_long_addition() {
  // Create vector
  Vector<long> v;
  v.insert( 1000L );
  v.insert( 2000L );
  v.insert( 3000L );
  // Create scalar
  long s = 2000L;
  // vector + scalar
  Vector<long> res = v + s;
  std::cout << "res = v + s = " << v << " + " << s << " = " << res << std::endl;
}

// vector + scalar (vector int and scalar float)
void test_vector_int_scalar_float_addition() {
  // Create vector
  Vector<int> v;
  v.insert( 1);
  v.insert( 2 );
  v.insert( 3 );
  // Create scalar
  float s = 2.1;
  // vector + scalar
  Vector<float> res = v + s;
  std::cout << "res = v + s = " << v << " + " << s << " = " << res << std::endl;
}

// scalar + vector (scalar int and vector int)
void test_scalar_int_vector_int_addition() {
  // Create scalar
  int s = 2;
  // Create vector
  Vector<int> v;
  v.insert( 1 );
  v.insert( 2 );
  v.insert( 3 );
  // scalar + vector
  Vector<int> res = s + v;
  std::cout << "res = s + v = " << s << " + " << v << " = " << res << std::endl;
}

// scalar + vector (scalar float and vector float)
void test_scalar_float_vector_float_addition() {
  // Create scalar
  float s = 2.1;
  // Create vector
  Vector<float> v;
  v.insert( 1.1 );
  v.insert( 2.1 );
  v.insert( 3.1 );
  // scalar + vector
  Vector<float> res = s + v;
  std::cout << "res = s + v = " << s << " + " << v << " = " << res << std::endl;
}

// scalar + vector (scalar double and vector double)
void test_scalar_double_vector_double_addition() {
  // Create scalar
  double s = 2.1;
  // Create vector
  Vector<double> v;
  v.insert( 1.1 );
  v.insert( 2.1 );
  v.insert( 3.1 );
  // scalar + vector
  Vector<double> res = s + v;
  std::cout << "res = s + v = " << s << " + " << v << " = " << res << std::endl;
}

// scalar + vector (scalar short and vector short)
void test_scalar_short_vector_short_addition() {
  // Create scalar
  short s = 2;
  // Create vector
  Vector<short> v;
  v.insert( 1 );
  v.insert( 2 );
  v.insert( 3 );
  // scalar + vector
  Vector<short> res = s + v;
  std::cout << "res = s + v = " << s << " + " << v << " = " << res << std::endl;
}

// scalar + vector (scalar long and vector long)
void test_scalar_long_vector_long_addition() {
  // Create scalar
  long s = 2000L;
  // Create vector
  Vector<long> v;
  v.insert( 1000L );
  v.insert( 2000L );
  v.insert( 3000L );
  // scalar + vector
  Vector<long> res = s + v;
  std::cout << "res = s + v = " << s << " + " << v << " = " << res << std::endl;
}

// scalar + vector (scalar int and vector float)
void test_scalar_int_vector_float_addition() {
  // Create scalar
  float s = 2.1;
  // Create vector
  Vector<int> v;
  v.insert( 1);
  v.insert( 2 );
  v.insert( 3 );
  // scalar + vector
  Vector<float> res = s + v;
  std::cout << "res = s + v = " << s << " + " << v << " = " << res << std::endl;
}

// vector + vector (vector int and vector int)
void test_vector_int_vector_int_addition() {
  // Create vector v1
  Vector<int> v1;
  v1.insert( 1 );
  v1.insert( 3 );
  v1.insert( 5 );
  // Create vector v2
  Vector<int> v2;
  v2.insert( 2 );
  v2.insert( 4 );
  v2.insert( 6 );
  // vector + vector
  Vector<int> res = v1 + v2;
  std::cout << "res = v1 + v2 = " << v1 << " + " << v2 << " = " << res << std::endl;
}

// vector + vector (vector float and vector float)
void test_vector_float_vector_float_addition() {
  // Create vector v1
  Vector<float> v1;
  v1.insert( 1.1 );
  v1.insert( 3.3 );
  v1.insert( 5.5 );
  // Create vector v2
  Vector<float> v2;
  v2.insert( 2.2 );
  v2.insert( 4.4 );
  v2.insert( 6.6 );
  // vector + vector
  Vector<float> res = v1 + v2;
  std::cout << "res = v1 + v2 = " << v1 << " + " << v2 << " = " << res << std::endl;
}

// vector + vector (vector double and vector double)
void test_vector_double_vector_double_addition() {
  // Create vector v1
  Vector<double> v1;
  v1.insert( 1.1 );
  v1.insert( 3.3 );
  v1.insert( 5.5 );
  // Create vector v2
  Vector<double> v2;
  v2.insert( 2.2 );
  v2.insert( 4.4 );
  v2.insert( 6.6 );
  // vector + vector
  Vector<double> res = v1 + v2;
  std::cout << "res = v1 + v2 = " << v1 << " + " << v2 << " = " << res << std::endl;
}

// vector + vector (vector short and vector short) -- does not work!!
void test_vector_short_vector_short_addition() {
  // Create vector v1
  Vector<short> v1;
  v1.insert( 1 );
  v1.insert( 3 );
  v1.insert( 5 );
  // Create vector v2
  Vector<short> v2;
  v2.insert( 2 );
  v2.insert( 4 );
  v2.insert( 6 );
  // vector + vector
  Vector<short> res = v1 + v2;
  std::cout << "res = v1 + v2 = " << v1 << " + " << v2 << " = " << res << std::endl;
}

// vector + vector (vector long and vector long)
void test_vector_long_vector_long_addition() {
  // Create vector v1
  Vector<long> v1;
  v1.insert( 10000000000L );
  v1.insert( 20000000000L );
  v1.insert( 30000000000L );
  // Create vector
  Vector<long> v2;
  v2.insert( 10000000000L );
  v2.insert( 20000000000L );
  v2.insert( 30000000000L );
  // vector + vector
  Vector<long> res = v1 + v2;
  std::cout << "res = v1 + v1 = " << v1 << " + " << v2 << " = " << res << std::endl;
}

// vector + vector (vector int and vector float)
void test_vector_int_vector_float_addition() {
  // Create vector v1
  Vector<int> v1;
  v1.insert( 1);
  v1.insert( 3 );
  v1.insert( 5 );
  // Create vector v2
  Vector<float> v2;
  v2.insert( 2.2 );
  v2.insert( 4.4 );
  v2.insert( 6.6 );
  // vector + vector
  Vector<float> res = v1 + v2;
  std::cout << "res = v1 + v2 = " << v1 << " + " << v2 << " = " << res << std::endl;
}

int main() {
  // Test vector + scalar operators
  test_vector_int_scalar_int_addition();
  test_vector_float_scalar_float_addition();
  test_vector_double_scalar_double_addition();
  test_vector_short_scalar_short_addition();
  test_vector_long_scalar_long_addition();
  test_vector_int_scalar_float_addition();

  // Test scalar + vector operators
  test_scalar_int_vector_int_addition();
  test_scalar_float_vector_float_addition();
  test_scalar_double_vector_double_addition();
  test_scalar_short_vector_short_addition();
  test_scalar_long_vector_long_addition();
  test_scalar_int_vector_float_addition();
  
  // Test vector + vector operators
  test_vector_int_vector_int_addition();
  test_vector_float_vector_float_addition();
  test_vector_double_vector_double_addition();
  test_vector_short_vector_short_addition();
  test_vector_long_vector_long_addition();
  test_vector_int_vector_float_addition();
  
  return 0;
}


