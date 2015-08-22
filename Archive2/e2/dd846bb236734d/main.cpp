#include <vector>

namespace 
{
    struct A
    {
        A( std::vector<int> vec ) : seq( std::move(vec) ) {}
        std::vector<int> seq ;
    };

    struct B
    {
        B( const std::vector<int>& vec ) : seq(vec) {}
        std::vector<int> seq ;
    };
}

std::vector<int> make_vector() ;

std::size_t pass_by_reference_to_const_and_copy()
{
    return B( make_vector() ).seq.size() ;
}
