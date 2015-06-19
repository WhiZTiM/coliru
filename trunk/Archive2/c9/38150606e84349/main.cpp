#include <iostream>
using namespace std;

template< typename T > class buffer
{
    public:
	T * data;
	buffer(){data = new T[10];}
    const T & operator [] ( size_t i) const {return data[i];}
          T & operator [] ( size_t i){return data[i];}

    operator const T * () const;
    operator       T * ();
};

int main() {
	buffer< int > buf;
    buf[ 0 ] = 0; // Generates an error
	return 0;
}