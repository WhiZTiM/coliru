// g++ -O3 question.cpp -o question.exe -I. --std=c++11 -lprotobuf-lite -lpthread -lz -losmpbf
#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/labeled_graph.hpp>
#include <boost/graph/iteration_macros.hpp>

typedef boost::adjacency_list<boost::listS,          // Store out-edges of each vertex in a std::list
                              boost::listS,          // Store vertex set in a std::list
                              boost::bidirectionalS, // The file dependency graph is directed
                              boost::property<boost::vertex_index_t, size_t>,    // vertex properties
                              boost::no_property     // edge properties
                              > AdjGraph;

int main() {
    AdjGraph g;

    std::map<size_t, AdjGraph::vertex_descriptor> vertex_map;
    
    for (int i = 1; i<6; ++i)
        vertex_map.emplace(10*i, add_vertex(10*i, g));

    boost::add_edge(vertex_map[10], vertex_map[30], g);
    boost::add_edge(vertex_map[10], vertex_map[50], g);
    boost::add_edge(vertex_map[30], vertex_map[40], g);
    boost::add_edge(vertex_map[50], vertex_map[20], g);

    auto index = boost::get(boost::vertex_index, g);

    BGL_FORALL_EDGES(e, g, AdjGraph) {
        auto source_n = boost::source(e, g);
        std::cerr << boost::get(index, source_n) << "\n";
    }
}

