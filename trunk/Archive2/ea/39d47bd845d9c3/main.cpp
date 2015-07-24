#include <fstream>
#include <iostream>
#include <vector>

struct Point {
    double x,y,z;

    double Distance(Point const& other) const {
        auto dx(other.x - x), dy(other.y - y), dz(other.z - z);
        return dx*dx + dy*dy + dz*dz;
    }
};

using Points = std::vector<Point>;

// make Point an adapted Fusion sequence
#include <boost/fusion/adapted.hpp>
#include <boost/fusion/include/io.hpp>
BOOST_FUSION_ADAPT_STRUCT(Point,(double,x)(double,y)(double,z))

// parse the input file
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp>

Points read_points(std::string const& fname) {
    Points points;

    std::ifstream ifs(fname);
    boost::spirit::istream_iterator f(ifs >> std::noskipws), l;

    namespace qi  = boost::spirit::qi;
    bool ok = qi::phrase_parse(f, l, 
            qi::omit [qi::lexeme[+qi::alnum] % ',' >> qi::eol] >> 
            *(qi::double_ >> ',' >> qi::double_ >> ',' >> qi::double_ >> qi::eol),
            qi::blank, points); 

    if (ok && f==l)
        return points;

    throw std::runtime_error("Parse incomplete at '" + std::string(f,std::max(std::next(f,16), l)) + "...'");
}

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>

int main() {
    using namespace boost;
    using Graph = adjacency_list<vecS, vecS, undirectedS, Point>;

    Graph g;
    for (auto& p : read_points("test.xyz"))
        add_vertex(p, g);


    double distance_thresh = 0;
    auto const vs = make_iterator_range(vertices(g));
    {
        namespace acc = boost::accumulators;
        acc::accumulator_set<double, acc::stats<acc::tag::mean, acc::tag::variance> > stats;

        for (auto it = vs.begin(); it != vs.end(); ++it)
            for (auto it2 = vs.begin(); it2 != vs.end(); it2++)
            {
                auto raw_dist = g[*it].Distance(g[*it2]);
                stats(sqrt(raw_dist));
            }

        auto mean       = acc::mean(stats);
        auto stddev     = sqrt(acc::variance(stats));
        distance_thresh = (mean - stddev)/4;

        std::cout 
            << " distance mean:"   << mean
            << " stddev:"          << stddev
            << " distance_thresh:" << distance_thresh << "²"
            << "\n";

        distance_thresh *= distance_thresh;
    }

    for(auto it = vs.begin(); it != vs.end(); ++it)
    {
        for (auto it2 = vs.begin(); it2 != vs.end(); it2++)
        {               
            double thisdist = g[*it].Distance(g[*it2]);
            if (thisdist < distance_thresh) {
                add_edge(*it,*it2, g);                  
            }
        }
    }

    print_graph(g);

    std::cout << "Done\n";
}
