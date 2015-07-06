#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>

struct Record {

    Record( double unit_price, int units, const std::string& descr ) 
        : unit_price(unit_price), units(units), descr(descr) {}
        
    double unit_price;
    int units;
    std::string descr ;
    //
};

int main()
{
    std::vector<Record> rec { {2.59,500,"apples"}, {4.25,100,"nectarines"}, {5.75,750,"uglis"}, {8.98,150,"pears"} };

    double total = accumulate( rec.begin(), rec.end(), 0.0,
        [] ( double v, const Record& r ) { return v + r.unit_price * r.units; } );
    std::cout << "total == " << total << '\n';

    total = accumulate( rec.begin(), rec.end(), 0.0,
        [] ( auto v, const auto& r ) { return v + r.unit_price * r.units; } ); // auto: C++14
    std::cout << "total == " << total << '\n';

}
