#include <iostream>
#include <sstream>
#include <locale>
#include <iomanip>
 
int main()
{
    std::tm tmb;
    std::istringstream ss(u8"6月");
    ss.imbue(std::locale("ja_JP.utf-8"));
    ss.exceptions(std::ios::failbit | std::ios::badbit);
    
    using CharT = char;
    using Traits = std::char_traits<CharT>;
    
    auto &&in = ss;
    auto &&fmt = "%B";
    
    typedef std::istreambuf_iterator<CharT, Traits> Iter;
    typedef std::time_get<CharT, Iter> TimeGet;
    std::ios_base::iostate err = std::ios_base::goodbit;
    const TimeGet& tg = std::use_facet<TimeGet>(in.getloc());
    tg.get(Iter(in.rdbuf()), Iter(), in, err, &tmb, fmt, fmt + Traits::length(fmt));
    if (err != std::ios_base::goodbit)
        in.setstate(err);
        
    std::cout << tmb.tm_mon;
}