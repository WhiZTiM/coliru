#include <boost/config.hpp>
#include <iostream>
#include <boost/graph/subgraph.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>

int main()
{
    using namespace boost;
    using containerS = vecS;
    typedef subgraph< adjacency_list<containerS, containerS, directedS,
            property<vertex_index_t, size_t>,
            property<edge_index_t, size_t>
        >
    > Graph;

    const int N = 6;
    Graph G0(N);
    enum { A, B, C, D, E, F}; 

    Graph& G1 = G0.create_subgraph();
    Graph::vertex_descriptor CG1 = add_vertex(G1);
    Graph::vertex_descriptor EG1 = add_vertex(G1);

    add_edge(CG1, EG1, G1);

    print_graph(G0);
    std::cout << "SUBGRAPH:\n";
    print_graph(G1);
}
