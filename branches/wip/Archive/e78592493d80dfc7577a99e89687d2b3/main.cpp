#include <boost/range/adaptor/adjacent_filtered.hpp>
#include <boost/range/algorithm.hpp>
#include <iostream>

int main(int argc, const char* argv[])
{
    using namespace boost::adaptors;
    std::string pi =
        "3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679"
        "8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196"
        "4428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273"
        "724587006606315588174881520920962829254091715364367892590360011330530548820466521384146951941511609";

    unsigned streak = 0;
    boost::adjacent_find(boost::sort(pi), [&](char a, char b) mutable { streak++; if (b!=a) {std::cout<<a<<':'<<streak<<';';streak=0;}; return false; });
    std::cout << "9:" << streak << "\n";
}
