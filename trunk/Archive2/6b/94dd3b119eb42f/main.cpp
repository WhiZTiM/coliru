#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <iomanip>

void test_it( std::vector<int>& seq, const char* tag )
{
    const auto start = std::clock() ;
    std::sort( seq.begin(), seq.end() ) ;
    const auto end = std::clock() ;
    std::cout << std::setw(30) << tag << ": " << std::setw(4)
              << (end-start) * 1000.0 / CLOCKS_PER_SEC << " millisecs\n" ;
}

int main()
{
    std::vector<int> seq( 8'000'000 ) ;
    test_it( seq, "all values compare equal" ) ;  

    std::iota( seq.rbegin(), seq.rend(), 0 ) ;
    test_it( seq, "pre-sorted in reverse order" ) ;  
    
    test_it( seq, "already sorted" ) ;  

    std::shuffle( seq.begin(), seq.end(), std::mt19937{} ) ; 
    test_it( seq, "shuffled (repeatable)" ) ;  
    
    std::mt19937 twister{ std::random_device{}() };
    twister.discard( twister.state_size ) ; 
    std::shuffle( seq.begin(), seq.end(), std::move(twister) ) ; 
    test_it( seq, "shuffled (random)" ) ;  
    
    
}
