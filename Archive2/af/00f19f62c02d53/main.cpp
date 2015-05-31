#include <range/v3/all.hpp>
#include <cstddef>
#include <iostream>

using namespace ranges;
using date = std::size_t;

auto month_number(date d)
{
    return d / 28;
}

auto week_number(date d)
{
    return d / 7;     
}

auto day_of_month(date d)
{
    return d % 28;    
}

auto day_of_week(date d)
{
    return d % 7;    
}

auto by_month()
{
    return view::group_by([](date a, date b){
        return month_number(a) == month_number(b);    
    });    
}

auto by_week()
{
    return view::group_by([](date a, date b){
        return week_number(a) == week_number(b);    
    });
}

auto month_by_week()
{
    return view::transform([](auto month){
        return month | by_week();
    });
}

int main() 
{
    auto year = view::iota(date{0}, date{364});
        
    RANGES_FOR(auto m, year | by_month() | month_by_week()) {
        RANGES_FOR(auto w, m)
            std::cout << (w | view::transform(day_of_month)) << '\n';
        std::cout << "----\n";            
    }    
}
