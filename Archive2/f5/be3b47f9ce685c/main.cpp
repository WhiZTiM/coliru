// g++ -O3 question.cpp -o question.exe
#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>

typedef long long node_id_t;

typedef boost::adjacency_list<boost::listS,          // Store out-edges of each vertex in a std::list
                              boost::listS,          // Store vertex set in a std::list
                              boost::bidirectionalS, // The file dependency graph is directed
                              node_id_t,             // vertex properties
                              boost::no_property     // edge properties
                              > AdjGraph;

int main() {
    AdjGraph g;

               add_vertex(10, g);
    auto v20 = add_vertex(20, g);
               add_vertex(30, g);
    auto v40 = add_vertex(40, g);
               add_vertex(50, g);

    add_edge(v40, v20, g);

    std::cout << "BEFORE:\n";
    print_graph(g, boost::get(boost::vertex_bundle, g));

    boost::graph_traits<AdjGraph>::vertex_iterator vi, vi_end, next;

    boost::tie(vi, vi_end) = boost::vertices(g);
    for (next = vi; vi != vi_end; vi = next) {
        ++next;
        if (boost::degree(*vi, g) == 0)
            boost::remove_vertex(*vi, g);
    }

    std::cout << "\n---\nAFTER:\n";
    print_graph(g, boost::get(boost::vertex_bundle, g));
}
