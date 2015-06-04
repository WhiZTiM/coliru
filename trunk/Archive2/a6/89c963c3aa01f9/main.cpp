#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/visitors.hpp>
#include <iterator>

using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS>;
using VertexPair = std::pair<Graph::vertex_descriptor, Graph::vertex_descriptor>;

struct Visitor : boost::default_dfs_visitor {
    using V = Graph::vertex_descriptor;

    void discover_vertex(V v, const Graph& /*g*/) {
        if (!root) {
            root = v;
        }
        if (!done) std::cerr << v << "\n";
    }

    void finish_vertex(V v, const Graph& /*g*/) {
        done |= (root == v);
    }
  private:
    bool done = false;
    boost::optional<V> root;
};

int main() {
    // [N0, N1[N2, N3, N4[N5], N6] :
    // VertexPair const data[] { {1, 2}, {1, 3}, {1, 4}, {4, 5}, };
    VertexPair const data[] { {0, 1}, {0, 2}, {0, 3}, {2, 4}, };
    Graph g(std::begin(data), std::end(data), 7);

    boost::depth_first_search(g, boost::visitor(Visitor()).root_vertex(2));
    //boost::write_graphviz(std::cout, g);
}
