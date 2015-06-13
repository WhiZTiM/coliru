#include <boost/functional/hash.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/stoer_wagner_min_cut.hpp>
#include <boost/property_map/property_map.hpp>

using namespace boost;

typedef adjacency_matrix<undirectedS> UGraph;

UGraph buildGraph() {
    UGraph g(10);

    // todo

    return g;
}

#include <iostream>

int main() {
    UGraph g = buildGraph(); // this function works fine

    int i = stoer_wagner_min_cut(g, boost::make_static_property_map<UGraph::edge_descriptor>(1));

    std::cout << "i: " << i << "\n";
}
