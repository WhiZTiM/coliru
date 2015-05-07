#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/reverse_graph.hpp>
#include <libs/graph/src/read_graphviz_new.cpp>

struct VertexInfo {
    std::string label;
};

struct EdgeInfo {
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, VertexInfo, EdgeInfo> Graph;

Graph read() {
    Graph g;

    using namespace boost;
    dynamic_properties dp;
    dp.property("node_id", get(&VertexInfo::label, g));
    read_graphviz("digraph { a -> b; a -> c; b -> d; b -> e; e -> f; e -> c; }", g, dp);

    return g;
}

int main() {
    using namespace boost;

    auto g = read();
    auto r = make_reverse_graph(g);

    write_graphviz(std::cout, r, make_label_writer(get(&VertexInfo::label, r)));
}
