#include <iostream>
#include <iomanip>

int main()
{
    int a[3][4] = { {0,1,2,3}, {4,5,6,7}, {8,9,10,11} };

    using row = int[4] ; // type of a row of the two-dimensional array 'a' is 'array of 4 int'
    const row* begin = a ; // 'pointer to const row' ie. 'pointer to const array of 4 int'
    const row* end = a+3 ;

    for( const row* p = begin ; p < end ; ++p )
    {
        // type of 'p' is 'pointer to const row' ie. 'pointer to const array of 4 int'
        // type of '*p' is 'const row' ie. 'const array of 4 int'
        const int* row_begin = *p ;
        const int* row_end = row_begin + 4 ;

        for( const int* q = row_begin ; q < row_end ; ++q ) std::cout << std::setw(3) << *q ;
        std::cout << "\n\n" ;
    }
}
