#include <string>
#include <iostream>

using namespace std;


template < typename Tn, typename ...P >
struct Vertex
{
    // split Tn into T[n]
    // http://en.cppreference.com/w/cpp/types/extent
    using T = decay<Tn>;
    static constexpr  unsigned int  n = extent<Tn>;
    
    T t[n];
    
    // want:
    //   Vertex<...P>  v;
    // unless termination (in which case int)
    conditional< (sizeof...(P)>0), Vertex<...P>, int >  v;
}

int main()
{
    using V = Vertex< float[3],  int[2],  double[4] >;
    cout << sizeof(V);
}