#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/random.hpp>
#include <boost/graph/graph_utility.hpp>
#include <random>

#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>

using boost::adaptors::transformed;
using namespace boost;

struct VertexCargo { int Id = rand() % 1024; };

typedef adjacency_list<setS, vecS, bidirectionalS, VertexCargo> Graph;

typedef graph_traits<Graph>::edge_descriptor   ED;
typedef graph_traits<Graph>::vertex_descriptor VD;

struct sourcer {
    using result_type = VD;

    Graph const* g;
    sourcer(Graph const& g) : g(&g) {}
    VD operator()(ED e) const { return boost::source(e, *g); }
};

struct targeter {
    using result_type = VD;

    Graph const* g;
    targeter(Graph const& g) : g(&g) {}
    VD operator()(ED e) const { return boost::target(e, *g); }
};

int main() {

    std::mt19937 rng { std::random_device{}() };

    Graph g;
    generate_random_graph(g, 1ul<<10, 1ul<<13, rng);

    for (auto v : make_iterator_range(vertices(g))) {
        std::cout << v <<  " --> ";

        //auto const& iel = boost::in_edge_list(g, v);
        //for (auto e : iel) std::cout << e.get_target() << " ";

        for (auto e : make_iterator_range(in_edges(v, g)))  std::cout << source(e, g) << " ";
        //for (auto e : make_iterator_range(out_edges(v, g))) std::cout << target(e, g) << " ";

        std::cout << "\n";

        assert(boost::is_sorted(make_iterator_range(in_edges(v,g))  | transformed(sourcer(g))));
        assert(boost::is_sorted(make_iterator_range(out_edges(v,g)) | transformed(targeter(g))));
    }
}
