#include <boost/graph/graphviz.hpp>
#include <boost/graph/random.hpp>
#include <random>

int main(int,char*[])
{
    using namespace boost;

    typedef boost::adjacency_list<setS, setS, DirectedS> Graph;
    Graph g;

    std::mt19937 prng{std::random_device{}()};
    generate_random_graph(g, 3, 5, prng);

    std::map<Graph::vertex_descriptor, size_t> ids;

    for (auto u : make_iterator_range(vertices(g)))
        ids[u] = ids.size();

    default_writer w;

    write_graphviz(std::cout, g, w, w, w, make_assoc_property_map(ids));
}
