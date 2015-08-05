#include <iostream>                  // for std::cout
#include <utility>                   // for std::pair
#include <algorithm>                 // for std::for_each
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace boost;

struct Node {
    int ilwisId;
};

typedef property<vertex_index_t, Node> wfVertexProperty;
typedef adjacency_list<vecS, vecS, bidirectionalS, wfVertexProperty> WorkflowGraph;

typedef property_map<WorkflowGraph, vertex_index_t>::type OperationIdMap;
typedef graph_traits<WorkflowGraph>::vertex_descriptor OperationNode;

int main(int,char*[]) {

    // create a typedef for the MyGraph type

    WorkflowGraph g;
    OperationIdMap index = get(vertex_index, g);
    Node aNode;
    aNode.ilwisId = 42;
    add_vertex(aNode, g);
    Node bNode;
    bNode.ilwisId = 6543;
    add_vertex(bNode, g);
    //add_edge(aNode, bNode, g);


    std::cout << "vertices(g) = ";
    typedef graph_traits<WorkflowGraph>::vertex_iterator vertex_iter;
    graph_traits<WorkflowGraph>::vertex_iterator vi, vi_end;
    for (tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi) {
        OperationNode v = *vi;
        std::cout << index[v] <<  " ";
    }
    std::cout << std::endl;


    std::cout << "edges(g) = ";
    graph_traits<WorkflowGraph>::edge_iterator ei, ei_end;
    for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
        std::cout << "(" << index[source(*ei, g)]
                  << "," << index[target(*ei, g)] << ") ";
    std::cout << std::endl;

}

