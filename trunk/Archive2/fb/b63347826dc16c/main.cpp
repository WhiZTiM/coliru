#include <iostream>
#include <iomanip>
#include <chrono>
#include <array>
using namespace std;

constexpr auto iterations = 1ull << 18;

template <class T, size_t N>
class SquareMatrix
{
     T M_matrix[N][N];
     
public:
       T& operator() (size_t i, size_t j)
       {
                  return M_matrix[i][j];
       }
       
       const T& operator() (size_t i, size_t j) const
       {
              return M_matrix[i][j];
       }
       


};


template <class T, size_t N>
class Vector
{
     array<T, N> M_array;
     
public:
       T& operator[](size_t i) 
       {
           return M_array[i];
       }
       
       const T& operator[](size_t i) const
       {
           return M_array[i];
       }
       
       template <typename Scalar>
       SquareMatrix<Scalar, 3> outerProduct(const Vector<Scalar, 3> &vec3) const
       {
          SquareMatrix<Scalar,3> result;
          for(unsigned int i = 0; i < 3; ++i)
              for(unsigned int j = 0; j < 3; ++j)
                  result(i,j) = (*this)[i] * vec3[j];
               
              
           
              
         return result;
       }


};

template<typename Scalar, size_t Dim>
void outerProduct(const Vector<Scalar, Dim> & v1 , const Vector<Scalar, Dim> & v2, SquareMatrix<Scalar, Dim> & m)
{
    for (unsigned int i=0; i<Dim; i++)
        for (unsigned int j=0; j<Dim; j++)
        {
            m(i,j) = v1[i] * v2[j];
        }
        
        
}
#pragma GCC optimize 0
void do_member()
{
  
  Vector<double, 3> vec1;
  Vector<double, 3> vec2;
  for (size_t i = 0; i < iterations; ++i)
    {
         SquareMatrix<double,3> m = vec1.outerProduct(vec2);
   
    }
  
}
#pragma GCC reset_options

#pragma GCC optimize 0
void do_global()
{
  Vector<double, 3> vec1;
  Vector<double, 3> vec2;
  SquareMatrix<double,3> m;
    for (size_t i = 0; i < iterations; ++i)
    {
         outerProduct(vec1, vec2, m);
         
    }
}
#pragma GCC reset_options

int main()
{
 
    
    cout << fixed << setprecision(15);
 

    SquareMatrix<double,3> m;
 
    auto now = chrono::steady_clock::now;
  
    auto begin = now();
         do_member();    
    auto end = now() - begin;
     
       
    
    auto begin2 = now();
         do_global();
    
    auto end2 = now() - begin2;
    
    // noisy stuff in asm - put on the bottom.
    cout << "Member outerProduct took: " << chrono::duration_cast< chrono::duration<double> >(end) .count() << "\n"
         << "Global outerProduct took: " << chrono::duration_cast< chrono::duration<double> >(end2).count() << "\n";
    
    
}