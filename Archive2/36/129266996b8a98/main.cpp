#include <iostream>
#include <string>
#include <vector>
#include <complex>

#include <algorithm>

using std::vector;
using Complex = std::complex<double>;
using VecCSizeType = vector<Complex>::size_type;


template <typename T>
void fftshift(vector<T> &input) {
  // input =  0 1 2 3 4 5 6 7 (input = 0 1 2 3 4 5 6 7 8)
  const auto N = input.size();                       /*N = 8 (N = 9)*/
  const auto kp = ceil(static_cast<double>(N) / 2);  /*kp = 4 (kp = 5)*/

  std::rotate(input.begin(),input.begin()+kp,input.end());
}


// ifftshift( 0 1 2 3 4 5 6 7 )   = 4 5 6 7 0 1 2 3
// ifftshift( 0 1 2 3 4 5 6 7 8 ) = 4 5 6 7 8 0 1 2 3
template <typename T>
void ifftshift(vector<T> &input) {
  const auto N = input.size();                       /*N = 8 (N = 9)*/
  const auto km = floor(static_cast<double>(N) / 2); /*km = 4 (km = 4)*/
  std::rotate(input.begin(), input.begin() + km, input.end());

}

int main()
{

std::vector<int> v = {0,1,2,3,4,5,6,7};
fftshift(v);
std::cout <<"even fftshift: ";
for(size_t i =0; i!= v.size();++i)
std::cout<<v[i];
std::cout<<std::endl;

std::vector<int> w = {0,1,2,3,4,5,6,7,8};
fftshift(w);
std::cout <<"odd fftshift: ";
for(size_t i =0; i!= w.size();++i)
std::cout<<w[i];
std::cout<<std::endl;


std::vector<int> q = {0,1,2,3,4,5,6,7};
fftshift(q);
std::cout <<"even ifftshift: ";
for(size_t i =0; i!= q.size();++i)
std::cout<<q[i];
std::cout<<std::endl;

std::vector<int> r = {0,1,2,3,4,5,6,7,8};
ifftshift(r);
std::cout <<"odd ifftshift: ";
for(size_t i =0; i!= r.size();++i)
std::cout<<r[i];
std::cout<<std::endl;

}
