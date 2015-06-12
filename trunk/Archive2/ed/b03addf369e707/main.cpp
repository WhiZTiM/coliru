#include <boost/graph/adjacency_list.hpp>
#include <boost/multi_array.hpp>

using namespace boost;

struct vertex_info {
    int id = []{ static int s_gen = 0; return ++s_gen; }();
};

struct edge_info {
};

struct graph_info {
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, vertex_info, edge_info, graph_info, boost::listS>
    Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor VertexDescriptor;
typedef boost::graph_traits<Graph>::edge_descriptor EdgeDescriptor;
typedef boost::graph_traits<Graph>::vertex_iterator VertexIterator;
typedef boost::graph_traits<Graph>::edge_iterator EdgeIterator;
typedef boost::graph_traits<Graph>::adjacency_iterator AdjacencyIterator;
typedef multi_array<int, 3> array3i;

class GraphService {
  private:
    Graph g;

  public:
    GraphService(Graph graph) { g = graph; }
    std::vector<int> get_adjacent(int i);
};

std::vector<int> GraphService::get_adjacent(int i)
{
    AdjacencyIterator first, last;
    std::vector<int> vertex_vector;
    vertex_vector.push_back(i);

    for (tie(first, last) = adjacent_vertices(i, g); first != last; ++first) {
        vertex_vector.push_back(g[*first].id);
    }

    return vertex_vector;
}

#include <iostream>
#include <boost/graph/random.hpp>
#include <random>

int main() {
    std::mt19937 prng { std::random_device{}() };
    Graph example;
    generate_random_graph(example, 100, 200, prng);

    GraphService let_clone_that(example);

    std::cout << "adjacent to 42: ";
    for(int v: let_clone_that.get_adjacent(42))
        std::cout << v << " ";
}
