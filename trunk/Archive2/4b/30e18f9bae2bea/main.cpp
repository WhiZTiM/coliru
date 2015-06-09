#include <iterator>
#include <algorithm>

int main()
{
    const int NROWS = 3 ;
    const int NCOLS = 4 ;
    int arr[NROWS][NCOLS] = { { 11, 12, 13, 14 }, { 21, 22, 23, 24 }, { 31, 32, 33, 34 } };

    int (*p)[4] = &arr[0];
    std::rotate( p, p + 1, p + 3 ); // *** error: array type 'int [4]' is not assignable (LLVM)
                                    // *** error: invalid array assignment (GNU)

    // or:
    // std::rotate( std::begin(arr), std::begin(arr) + 1, std::end(arr) );
}
