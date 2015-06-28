#include <iostream>
#include <cstdio>
#include <ctime>
#include <algorithm>

int main()
{
    const std::size_t NEVENTS = 20 ;
    const std::size_t NRANDOMLY_CHOSEN = 5 ;

    // create a sequence of NEVENTS events 0, 1, 2 ... NEVENTS-1
    int events[NEVENTS] ;
    for( std::size_t i  = 0 ; i < NEVENTS ; ++i ) events[i] = i ;

    // shuffle the sequence randomly http://en.cppreference.com/w/cpp/algorithm/random_shuffle
    std::srand( std::time(0) ) ;
    std::random_shuffle( events, events+NEVENTS ) ;

    std::cout << "the randomly chosen event numbers are: " ;
    // select the first NRANDOMLY_CHOSEN events in the sequence
    for( std::size_t i = 0 ; i < NRANDOMLY_CHOSEN ; ++i ) std::cout << events[i] << ' ' ;
    std::cout << '\n' ;
}
