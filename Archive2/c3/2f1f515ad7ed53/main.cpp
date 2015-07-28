#include <iostream>
#include <string>
#include <vector>

// converts all boost exceptions to global function call
#define BOOST_EXCEPTION_DISABLE
#define BOOST_NO_EXCEPTIONS         // exception handling is forwared to a global function

#include <boost/lexical_cast.hpp>   // boost code with which we throw exceptions
#include <boost/exception/all.hpp>  // needed for diagnostic_information<T>(exception)


// Global function to handle exceptions
// when BOOST_NO_EXCEPTIONS is defined
namespace boost {
    // function signature is fixed.
    void throw_exception( std::exception const & e )
    {
        std::cout << "Exception arrived: " << e.what() << std::endl;
        std::cout << "Diagnostic info:" << diagnostic_information<std::exception>(e) <<std::endl;
    }
}

int main(){

    std::string dwarves( "7" );
    std::string balloons( "99 red ballons" );
    
    int noDwarves  = boost::lexical_cast<int>(dwarves);
    int noBalloons = boost::lexical_cast<int>(balloons);      // throws exception from boost
    
    std::cout << "There are " << noDwarves << " dwarves in Grimm's tale." << std::endl;
    std::cout << "There are " << noBalloons << " red ballons in the title of the song. " <<std::endl;
}

