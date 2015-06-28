#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

int main()
{
    const std::size_t NEVENTS = 20 ;
    const std::size_t NRANDOMLY_CHOSEN = 5 ;

    // create a sequence of NEVENTS events
    std::vector<std::string> events ;
    for( std::size_t i  = 0 ; i < NEVENTS ; ++i ) events.push_back( "event #" + std::to_string(i) ) ;

    // shuffle the sequence randomly http://en.cppreference.com/w/cpp/algorithm/random_shuffle
    std::shuffle( std::begin(events), std::end(events), std::mt19937( std::random_device()() ) ) ;

    // select the first NRANDOMLY_CHOSEN events in the sequence
    for( std::size_t i = 0 ; i < NRANDOMLY_CHOSEN ; ++i ) std::cout << i+1 << ". " << events[i] << '\n' ;
}
