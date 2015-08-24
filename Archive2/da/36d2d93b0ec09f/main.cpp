#include<iostream>
#include<vector>
// #include<complex>
#include<algorithm> 

// using std::ostream;
using std::cout;
using std::endl;
using std::vector;
// using std::complex;

template <typename T> struct identity { using type = T; };
template <typename T> using identity_t = typename identity<T>::type;

template<typename T>
vector <T> lift_binary (const vector<T> & v1, const vector<T> & v2, identity_t<T(T, T)>* bf)
{   auto result = vector<T> ();
    result.resize(v1.size());
    transform (v1.begin(), v1.end(), v2.begin(), result.begin(), bf);
    return result;   }

template<typename T>
T minus (T x, T y)
{   return x - y;   }

template<typename T>
vector<T> operator- (const vector<T> &v1, const vector<T> &v2)
// {   return lift_binary (v1, v2, [] (T x, T y) -> T { return x - y; } );   }
// {   return lift_binary (v1, v2, [] (T x, T y) { return x - y; } );   }
   {   return lift_binary (v1, v2, [] (auto x, auto y) { return x - y; } );   }
// {   return lift_binary (v1, v2, minus);   }

template<typename T>
vector<T> operator+(const vector<T> & v1, const vector<T> & v2)
{   return lift_binary (v1, v2, [] (T x, T y) -> T { return x + y; } );   }
    
int main()
{   auto v1 = vector<double> ({1, 2, 3});
    auto v2 = vector<double> ({10, 20, 30});
    auto v3 = v1 - v2;
    cout << v3[0] << " " 
         << v3[1] << " " 
         << v3[2] << " " << endl;
    return 0;
}
    
    
    