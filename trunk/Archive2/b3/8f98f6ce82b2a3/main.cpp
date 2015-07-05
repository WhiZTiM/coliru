#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

struct Record {
    double unit_price;
    int units;
    //
};

int main()
{
    std::vector<Record> rec { {2.59, 500}, {4.25,100}, {5.75,750}, {8.98,150} };

    double total = accumulate( rec.begin(), rec.end(), 0.0,
        [] ( double v, const Record& r ) { return v + r.unit_price * r.units; } );
    std::cout << "total == " << total << '\n';

    total = accumulate( rec.begin(), rec.end(), 0.0,
        [] ( auto v, const auto& r ) { return v + r.unit_price * r.units; } ); // auto: C++14
    std::cout << "total == " << total << '\n';

}
