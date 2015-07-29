#include <iostream>
#include <vector>
#include <fstream>
#include <utility>

using Point = std::pair<int,int> ;

std::ostream& operator<< ( std::ostream& os, const Point& p )
{ return os << '(' << p.first << ',' << p.second << ')'; }

std::istream& operator>>( std::istream& is, Point& p )
{
    int x, y;
    char ch1, ch2, ch3;

    if( is >> ch1 >> x >> ch2 >> y >> ch3 &&
        ch1 == '(' && ch2 == ',' && ch3 == ')' ) p = {x,y}; // validate
    else is.setstate( is.rdstate() | std::ios_base::failbit ) ; // input failed

    return is;
}

int main()
{
    //read data from keyboard into vector op.
    std::vector<Point> op;

    std::cout << "Enter points one by one, eof to end input\n";
    int x, y;
    while( std::cin >> x >> y ) op.emplace_back( x, y ); // construct Point directly in the vector
    // http://en.cppreference.com/w/cpp/container/vector/emplace_back

    // write the data to the screen using user defined output operator
    for( Point p : op ) std::cout << p << '\n';

    // write the data to a text file using user defined output operator
    // canonical: if the file was opened, write every object in the sequence to the file
    if( std::ofstream ost{ "data.txt" } ) for( Point p : op )   ost << p << '\n';
    else std::cerr << "error opening output file\n" ;
    // the output stream ost is destroyed when it goes out of scope

    // read data from text file using user defined input operator
    std::vector<Point> ip;
    Point p;
    if( std::ifstream ist{ "data.txt" } ) while( ist >> p ) ip.push_back(p) ;
    else std::cerr << "error opening input file\n" ;

    // verify that the two vectors are equal (lexicographically equal)
    if( ip == op ) std::cout << "read back the points successfully\n" ;
    else std::cerr << "error in i/o of point\n" ;

    // write data to screen using user defined output operator
    for( auto p : ip ) std::cout << p << '\n';
}
