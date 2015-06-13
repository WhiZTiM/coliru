#include <iostream>
#include <vector>

// trivially range-checked vector (no iterator checking):
template< class T> struct Vector : public std::vector<T> {

    typedef typename std::vector<T>::size_type size_type;

    using std::vector<T>::vector ; // inherit all constructoes

	T& operator[](unsigned int i) { return std::vector<T>::at(i); }

	const T& operator[](unsigned int i) const { return std::vector<T>::at(i); }
};

int main()
{
    Vector<int> a { 1,2,3,4 } ; // direct initialisation
    Vector<int> b = { 1,2,3,4 } ; // copy initialisation
    if( a == b ) std::cout << "ok.\n" ;
}
