#include <boost/graph/adjacency_list.hpp>

using namespace boost;
using Graph = adjacency_list<vecS, vecS, bidirectionalS>;

#include <boost/graph/graph_utility.hpp> // for display

int main() {
    Graph g;
    auto a = add_vertex(g);
    auto b = add_vertex(g);

    add_edge(a,b,g);

    print_graph(g);
}
