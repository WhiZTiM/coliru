#include <iostream>
#include <random> // ***
#include <ctime>

int main()
{
    // create the pseudo random number generator seeded with a somewhat random value
    std::mt19937 rng( std::time(nullptr) ) ;
    rng.discard( std::mt19937::state_size ) ; // let it warm up

    // create a random number distribution
    std::uniform_int_distribution<int> distrib( 1, 100 ) ; // integers uniformly distributed in [1,100]

    // generate and print out a few pseudo random numbers evenly distributed in [1,100]
    for( int i = 0 ; i < 20 ; ++i ) std::cout << distrib(rng) << ' ' ;
    std::cout << '\n' ;
}
