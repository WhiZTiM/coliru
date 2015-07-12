//    C21 I-O.cpp
#include <iostream>
#include <map>
#include <string>
#include <sstream>

std::ostream& operator<< ( std::ostream& os, const std::map< std::string, int >& map ) {

    os << "{ " ;
    for( const auto& pair : map ) os << "{'" << pair.first << "'," << pair.second << "} " ;
	return os << "}";
}

std::istream& operator>> ( std::istream& is, std::map<std::string, int>& map ) {

    map.clear() ;

    std::string str ;
    int i ;
    while( is >> str >> i ) map.emplace( str, i ) ;

    if( !map.empty() ) { is.clear() ; is.ignore(1000,'\n') ; }
    return is ;
}

int main() {

	std::map<std::string, int> msi;

	std::istringstream str_in( "map 34 set 9 string 26 vector 5 istream 1001 stringbuf 87" ) ;
	str_in >> msi;

	std::cout << msi << '\n';
}
