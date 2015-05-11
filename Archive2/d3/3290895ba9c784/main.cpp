#include <iostream>
#include <random>
#include <vector>
#include <algorithm>


void just_accumulate( std::vector<double> & v )
{
    std::stable_sort(v.begin(), v.end());
    size_t smallest_sum_idx = 0;
    size_t smalles_sum_size = 1;
    size_t current_array_ptr = 2;
    v[0] += v[1];
    while( current_array_ptr != v.size )
    {
        
    }
}


int main()
{
    std::random_device rd;
 
    std::mt19937 e2(rd());
    std::normal_distribution<> normal_dist(1e3, 1e2);
    
    const size_t arr_size = 10;
    std::vector<double> v(arr_size);
    std::generate(v.begin(), v.end(), [&](){ return normal_dist(e2); } );
    just_accumulate(v);
    
    for ( size_t i = 0; i < arr_size; ++i)
        std::cout << v[i] << std::endl;
}
