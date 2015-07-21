#include <boost/graph/adjacency_list.hpp>
#include <iostream>

typedef boost::adjacency_list<boost::setS,boost::setS,boost::undirectedS, uint32_t, float> AdjacencyList;
typedef boost::graph_traits<AdjacencyList>::adjacency_iterator AdjacencyIterator;

int main() {
    AdjacencyList adjacency_list, supervoxel_adjacency_list;

    boost::add_edge(
            boost::add_vertex(10, adjacency_list),
            boost::add_vertex(20, adjacency_list),
            1.5f,
            adjacency_list
        );

    boost::add_edge(
            boost::add_vertex(30, adjacency_list),
            boost::add_vertex(40, adjacency_list),
            2.5f,
            adjacency_list
        );

    AdjacencyList::vertex_iterator i, end;

    for (boost::tie(i, end) = boost::vertices(adjacency_list); i != end; i++) {
        AdjacencyIterator ai, a_end; 

        boost::tie(ai, a_end) = boost::adjacent_vertices(*i, supervoxel_adjacency_list);
        for (; ai != a_end; ai++) { 
            std::cout << adjacency_list[*ai] << "\t";
        }
    }
}
