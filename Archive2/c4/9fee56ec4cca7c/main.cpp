// g++ -O3 question.cpp -o question.exe
#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/labeled_graph.hpp>
#include <boost/graph/iteration_macros.hpp>

typedef long long node_id_t;

typedef boost::adjacency_list<boost::listS,          // Store out-edges of each vertex in a std::list
                              boost::listS,          // Store vertex set in a std::list
                              boost::bidirectionalS, // The file dependency graph is directed
                              boost::no_property,    // vertex properties
                              boost::no_property     // edge properties
                              > AdjGraph;

typedef boost::labeled_graph<AdjGraph,
                             node_id_t // Node ID
                             > LabeledGraph;

int main() {
    LabeledGraph g;

    add_vertex(10, g);
    add_vertex(20, g);
    add_vertex(30, g);
    add_vertex(40, g);
    add_vertex(50, g);

    boost::graph_traits<LabeledGraph>::vertex_iterator vi, vi_end, next;

    AdjGraph& underlying = g.graph();

    boost::tie(vi, vi_end) = boost::vertices(underlying);
    for (next = vi; vi != vi_end; vi = next) {
        ++next;
        if (boost::degree(*vi, underlying) == 0)
            boost::remove_vertex(*vi, underlying);
    }
}
