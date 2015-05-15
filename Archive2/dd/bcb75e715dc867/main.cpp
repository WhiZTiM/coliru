#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/random.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/iteration_macros.hpp>

#include <random>
#include <iostream>

using namespace boost;

namespace topologicalmap {
    struct Intersection_Graph {
        std::string bundled;
    };
}

typedef boost::adjacency_list<
        boost::listS, boost::listS, boost::undirectedS, 
        boost::property<boost::vertex_index_t, int, topologicalmap::Intersection_Graph>,
        boost::edge_weight_t, 
        boost::no_property > Graph_boost;

int main() {

    std::mt19937 prng { std::random_device {} () };
    Graph_boost g;

    generate_random_graph(g, 10, 20, prng);

    // assign indices
    int i = 0;
    BGL_FORALL_VERTICES(v, g, Graph_boost) { 
        get(vertex_index, g)[v] = i; 
        g[v].bundled = "id:" + std::to_string(i);

        i++;
    }
    
    // print the graph using the `bundled` property as a label:
    print_graph(g, get(&topologicalmap::Intersection_Graph::bundled, g));

    // do some index accesses:
    for (int i : {1,7})
        std::cout << "\nVertex at index #" << i << " has a bundled property of '" << g[vertex(i,g)].bundled << "'";
}
