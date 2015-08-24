
#include <boost/version.hpp>
//#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
#include <cstdint>
#include <iostream>
#include <locale>

int main()
{
    
    std::cout << BOOST_LIB_VERSION << "\n";
    
    //bool b = true;
    //std::int64_t i = 55;
    
    //std::cout << " b -> int64 " << boost::lexical_cast< std::int64_t >(b) << "\n";
    //std::cout << " int64 -> b " << boost::lexical_cast< bool >(i)  << "\n";
    
    //auto facet = std::use_facet< boost::filesystem::path::codecvt_type >(std::locale("ru_RU.utf8"));
    
    boost::filesystem::path toto("1/2\u0438\u0439", std::use_facet< boost::filesystem::path::codecvt_type >(std::locale("ru_RU.utf8")));

    std::cout << toto << "\n";
    
    
    return 0;
}
