#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi_match.hpp>

template <typename Graph>
bool read_coloring_problem(std::istream& dimacs, Graph& g) {
    auto add_edge_ = [&g](size_t from, size_t to) { add_edge(from, to, g); };
    size_t vertices = 0, edges = 0;

    using namespace boost::spirit::qi;
    namespace px = boost::phoenix;
    uint_parser<size_t> num_;

    auto eoil      = eol | eoi;
    auto comment   = boost::proto::deep_copy(lexeme["c " >> *(char_ - eol) >> eoil] | eol);
    auto vertices_ = px::ref(vertices);
    auto edges_    = px::ref(edges);

    dimacs >> std::noskipws >> phrase_match(
            *comment >>
            ("p" >> lit("edge") >> num_ [vertices_ = _1] >> num_ [edges_ = _1] >> eoil) >>
            repeat(edges_) [ 
            *comment >> ("e" >> num_ >> num_ >> eoil) [ px::bind(add_edge_, _1-1, _2-1) ]
            ] 
            >> *comment >> eoi
            , blank);

    return dimacs.good() || dimacs.eof();
}

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <fstream>
#include <iostream>

using namespace boost::graph;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;

int main() {
    Graph g2;
    std::ifstream input("myciel4.col");
    if (read_coloring_problem(input, g2))
    {
        std::cout << "Nodes: " << num_vertices(g2) << "\n";
        std::cout << "Edges: " << num_edges(g2)    << "\n";
        boost::write_graphviz(std::cout, g2);
    } else {
        std::cout << "Parse error\n";
    }
}
