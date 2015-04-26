#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_match.hpp>
#include <fstream>
#include <iostream>
namespace qi = boost::spirit::qi;

struct measure {
    int id;
    double x, y, size_, angle;
};

BOOST_FUSION_ADAPT_STRUCT(measure, (int, id)(double, x)(double, y)(double, size_)(double, angle))

struct KeyPoint {
    KeyPoint(measure const& m) {
        std::cout << "Debug: " << __FUNCTION__ << "(" << m.x << ", " << m.y << ", " << m.size_ << ", " << m.angle << ")\n";
    }
};

void RelativeMeasure(std::string filename)
{
    std::ifstream calfile(filename, std::ios::binary);

    int key_count;
    std::vector<measure> measure_list;

    using namespace qi;
    if (
           calfile >> std::noskipws >> phrase_match(int_, blank, key_count)
        && calfile >> phrase_match(qi::repeat(key_count)[int_ > double_ > double_ > double_ > double_ > +eol], blank, measure_list)
    )
    {
        std::vector<KeyPoint> key_list;
        key_list.reserve(measure_list.size());
        // using a converting constructor (why not parse into this at once?)
        std::copy(measure_list.begin(), measure_list.end(), back_inserter(key_list));
    }
}

int main() {
    RelativeMeasure("input.txt");
}
