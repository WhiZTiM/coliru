#include <boost/graph/graphviz.hpp>
#include <boost/graph/random.hpp>
#include <random>

int main(int,char*[])
{
    using namespace boost;

    typedef boost::adjacency_list<
        boost::setS,        // outedge list
        boost::setS,        // vertex list
        boost::directedS,   // undirected
        boost::no_property, // vertex prop
        boost::no_property, // edge prop
        boost::no_property, // graph prop
        boost::vecS         // edgelistc
    > Graph;
    Graph g;

    std::mt19937 prng{std::random_device{}()};
    generate_random_graph(g, 3, 5, prng);

    std::map<Graph::vertex_descriptor, size_t> ids;

    for (auto u : make_iterator_range(vertices(g)))
        ids[u] = ids.size();

    default_writer w;

    write_graphviz(std::cout, g, w, w, w, make_assoc_property_map(ids));
}
