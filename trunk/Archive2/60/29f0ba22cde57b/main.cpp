#include <iostream>
#include <utility>

#include <cstdlib>

struct I { constexpr operator std::index_sequence< 0, 1, 2 > () const { return {}; } };

template< std::size_t M, std::size_t N > // M - arity, N - number of types
struct test
{
    
    template< std::size_t ...i >
    void
    operator () (std::index_sequence< i... > = I{}) const
    {
        std::size_t indices[M];
        for (std::size_t & m : indices) {
            m = 0;
        }
        for (;;) {
            (std::cout << ... << indices[i]) << std::endl;
            std::size_t m = 0;
            for (;;) {
                std::size_t & n = indices[m];
                ++n;
                if (n != N) {
                    break;
                }        
                n = 0; 
                if (++m == M) {
                    return;
                }
            }
        }
    }
    
};

int
main()
{  
    test< 3, 3 >{}(); // hard error
    test< 3, 3 >{}(std::make_index_sequence< 3 >{});
    return EXIT_SUCCESS;
}