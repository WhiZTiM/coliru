#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

int main()
{
    using namespace boost;
    typedef adjacency_list<vecS, vecS, directedS, no_property, int> Graph;
    Graph g;
    add_edge(0, 1, 123, g);
    write_graphviz(std::cout, g, default_writer(), make_label_writer(boost::get(edge_bundle,g)));
}
