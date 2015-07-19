#include <ostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>
#include <algorithm>

struct Range
{
    friend std::istream& operator>>(std::istream& is, Range& p);
    friend std::ostream& operator<<(std::ostream& os, const Range& p);

    int lower;
    int bigger;
};

std::istream& operator>>(std::istream& is, Range& p)
{
    is.ignore(1, '[');
    std::string s;
    std::getline(is, s, ']');

    auto commaPos = std::find(s.begin(), s.end(), ',');

    p.lower = std::stoi(std::string{s.begin(), commaPos});
    p.bigger = std::stoi(std::string{std::next(commaPos, 2), s.end()});

    return is;
}

std::ostream& operator<<(std::ostream& os, const Range& p)
{
    return os << "[" << p.lower << ", " << p.bigger << "]";
}

struct Period
{
    friend std::istream& operator>>(std::istream& is, Period& p);
    friend std::ostream& operator<<(std::ostream& os, const Period& p);

    std::string name;
    std::vector<Range> ranges;
};

std::istream& operator>>(std::istream& is, Period& p)
{
    std::getline(is, p.name, ':');
    
    is.ignore(std::numeric_limits<std::streamsize>::max(), '[');
    do
    {
        Range r;
        is >> r;
        p.ranges.push_back(r);
    } while(!(is.ignore(std::numeric_limits<std::streamsize>::max(), ' ').eof()));

    return is;
}

std::ostream& operator<<(std::ostream& os, const Period& p)
{
    os << p.name << ": [";
    for(auto a = p.ranges.begin(); a != std::prev(p.ranges.end()); ++a)
        os << *a << ", ";
    os << *(std::prev(p.ranges.end())) << "],";

    return os;
}


int main()
{
    {
    std::fstream outputFileStream("myinputfile", std::ios::out);
    outputFileStream << "A: [[1, 95], [78, 110]],\nB: [[85, 86], [88, 93], [96, 156], [158, 442]],";
    }
    {
    std::vector<Period> periods;

    std::fstream inputFileStream("myinputfile", std::ios::in);
    for(std::string s; std::getline(inputFileStream, s); )
    {
        periods.push_back(Period());

        std::stringstream ss(s);
        ss >> periods.back();
    }

    for(const auto& a : periods)
    {
        std::cout << "Period : " << a.name << " with ranges ";
        for(auto b = a.ranges.begin(); b != std::prev(a.ranges.end()); ++b)
            std::cout << b->lower << "-" << b->bigger << ", ";
        auto last = std::prev(a.ranges.end());
        std::cout << last->lower << "-" << last->bigger << std::endl;
    }
    }
    std::remove("myinputfile");
}