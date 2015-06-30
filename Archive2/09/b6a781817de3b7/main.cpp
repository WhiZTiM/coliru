#include <boost/graph/adjacency_list.hpp>

using namespace boost;
typedef boost::adjacency_list<setS, vecS, directedS, std::string, char> MyGraph;
typedef boost::graph_traits<MyGraph>::vertex_descriptor Vertex;
typedef boost::graph_traits<MyGraph>::edge_descriptor Edge;

int main() {
    MyGraph g;

    // setup
    add_vertex(std::string("xxx"), g);
    Vertex currentVertex = g.vertex_set()[0];
    Vertex endVertex = add_vertex(std::string("yyy"), g);
    Edge i_edge = add_edge(currentVertex, endVertex, 'i', g).first;

    // later...
    // Now I want that edge containing the letter 'i'.
    char yougotit = g[i_edge];
    assert('i' == yougotit);
}