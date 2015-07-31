#include <iostream>
#include <string>
#include <type_traits>
#include <iterator>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <ctime>
#include <array>



template<typename Left, typename Op, typename Right>
struct Expression
{
public:
  Expression(Left&& l1, Right& r1) : _left(std::move(l1)) , _right(std::move(r1)) {}
  
  auto operator[](int index) 
  {
      return Op{} (_left[index],_right[index]); // any callable
  }
  
private:
  Left  _left;
  Right _right;
  
};

template<typename T>
struct Array
{
  public:
  
  Array(T* ptr, int size) : _data(ptr) , N(size) {}
  
  template<typename Left, typename Op, typename Right>
  Array& operator= (Expression<Left,Op,Right> expr)
  {
      // need to do this manual loop to call the operator[] from the expression which does the operations specified
      for(int i = 0; i < N; ++i)
      {
          _data[i] = expr[i]; 
      }
      return *this;
  }
  
  T operator[] (int index)
  {
    return _data[index];   
  }
  
  
  
  private:
  T* _data;
  int N;
  
};


// lets implement operator+
template<typename Left, typename T>
Expression<Left,std::plus<T>,Array<T>> operator +(Left l1, Array<T> ar)
{
    return Expression<Left,std::plus<T>,Array<T>>{std::move(l1),ar};
}







int main()
{
   constexpr int vec_size = 300000;
   std::srand(std::time(0));
   std::array<double,vec_size> vec1;
   std::array<double,vec_size> vec2;
   std::array<double,vec_size> results;
   
   std::iota(vec1.begin(),vec1.end(),rand()%500);
   std::iota(vec2.begin(),vec2.end(),rand()%375);
   
   Array<double> a1(vec1.data(),vec_size);
   Array<double> a2(vec2.data(),vec_size);
   
   Array<double> a3(results.data(),vec_size);
   
   a3 = a1 + a2;
//   std::copy(vec1.begin(),std::next(vec1.end(),10),std::ostream_iterator<double>(std::cout,", "));
//   std::cout << '\n';
//   std::copy(vec2.begin(),vec2.end(),std::ostream_iterator<double>(std::cout,", "));
//   std::cout << '\n';
   std::copy(results.begin(),std::next(results.begin(),10),std::ostream_iterator<double>(std::cout,", "));
   
}
