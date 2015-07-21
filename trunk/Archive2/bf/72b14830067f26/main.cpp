#include <boost/graph/adjacency_list.hpp>
#include <iostream>

typedef boost::adjacency_list<
    boost::multisetS,
    boost::vecS, 
    boost::directedS,
    boost::no_property,
    boost::no_property,
    boost::no_property,
    boost::setS 
    > Graph;

typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef typename boost::graph_traits<Graph>::edge_descriptor Edge;

void test(Edge aE, const Graph &aG) {
    Vertex sv = boost::source(aE, aG);
    Vertex tv = boost::target(aE, aG);
    typename boost::graph_traits<Graph>::out_edge_iterator it, eit;
    for (boost::tie(it, eit) = boost::edge_range(sv, tv, aG);
        it != eit;
        ++it) {
    }
}

int main() {
    std::cout << "asdfsd" << std::endl;
}
