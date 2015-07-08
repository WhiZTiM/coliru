#include <iostream>
#include <string>
#include <vector>

std::vector<std::size_t> locate_all( const std::vector<std::string>& seq, const std::string& what )
{
    std::vector<std::size_t> result ;
    for( std::size_t i = 0 ; i < seq.size() ; ++i ) if( seq[i] == what ) result.push_back(i) ;
    return result ;
}

int main()
{
    const std::string cat = "cat" ;
    const std::vector<std::string> my_words { "cat", "dog", cat, "bird", cat, "cat", "elephant", cat };


    std::cout << "word '" << cat << "' was found at positions: " ;
    for( auto pos : locate_all( my_words, cat ) ) std::cout << pos << ' ' ;
    std::cout << '\n' ;
}
