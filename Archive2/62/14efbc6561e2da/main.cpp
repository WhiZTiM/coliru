#include <boost/graph/graphviz.hpp>
#include <boost/graph/random.hpp>
#include <random>

int main(int,char*[])
{
    using namespace boost;

    typedef boost::adjacency_list<setS, setS, directedS, property<vertex_index_t, size_t> > Graph;
    Graph g;

    std::mt19937 prng{std::random_device{}()};
    generate_random_graph(g, 3, 5, prng);

    auto ids = get(vertex_index, g);
    size_t num = 0;
    for (auto u : make_iterator_range(vertices(g)))
        put(ids, u, num++);

    write_graphviz(std::cout, g);
}
