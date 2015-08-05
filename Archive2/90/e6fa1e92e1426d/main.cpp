#include <iostream>
#include <climits> // UINT_MAX

unsigned int find( unsigned int sought, const unsigned int arr[], unsigned int arr_sz ) ;

int main() {

    const unsigned int ARRAY_SIZE = 6 ;
    const unsigned int a[ARRAY_SIZE] = { 11, 22, 33, 44, 33, 55 };
                          // positions:   0   1   2   3   4   5

	unsigned int sought = 11 ;
	std::cout << "Find value " << sought << ": " << find( sought, a, ARRAY_SIZE ) << '\n' ;

	sought = 33 ;
	std::cout << "Find value " << sought << ": " << find( sought, a, ARRAY_SIZE ) << '\n' ;

	sought = 55 ;
	std::cout << "Find value " << sought << ": " << find( sought, a, ARRAY_SIZE ) << '\n' ;

	sought = 92 ;
	std::cout << "Find value " << sought << ": " << find( sought, a, ARRAY_SIZE ) << '\n' ;
}

unsigned int find( unsigned int sought, const unsigned int arr[], unsigned int arr_sz )
{
    for( unsigned int pos = 0 ; pos < arr_sz ; ++pos ) {
        if( arr[pos] == sought ) return pos ; // found at position pos
    }

    return UINT_MAX ; // not found
}
