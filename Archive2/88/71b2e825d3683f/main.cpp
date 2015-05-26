#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/copy.hpp>
#include <iostream>

struct Vertex {
    std::string name;
};

struct Edge {
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, Vertex, Edge > Graph;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, Vertex, Edge > UndirectedGraph; 

Graph network;

int greedy_colouring() {
    using namespace boost;
    typedef boost::graph_traits<UndirectedGraph>::vertex_descriptor  vertex_descriptor;
    static_assert(is_integral<vertex_descriptor>::value, "IndexMap not provided yet TODO");

    typedef boost::graph_traits<UndirectedGraph>::vertex_iterator    vertex_iter;
    typedef boost::graph_traits<UndirectedGraph>::adjacency_iterator adjacency_it;

    // create an undirected graph with the vertices and edges of the first one
    UndirectedGraph g;
    copy_graph(network, g);

    vertex_iter vit, vend;
    tie(vit, vend) = vertices(g);

    size_t const vertices_amount = num_vertices(g);
    std::vector<int> vertex_colouring(vertices_amount, -1);
    vertex_colouring[*vit] = 0; // Assign the first color to first vertex
    
    // A temporary array to store the available colors. 
    // - available[cr]:  assigned to one of its adjacent vertices
    std::vector<bool> available(vertices_amount, false);

    tie(vit, vend) = vertices(g);
    for (++vit; vit!=vend; ++vit)
    {
        // Process all adjacent vertices and flag their colors
        // as unavailable
        adjacency_it neighbour, neighbour_end;
        for (tie(neighbour, neighbour_end) = adjacent_vertices(*vit, g); neighbour != neighbour_end; ++neighbour)
            if (vertex_colouring[*neighbour] != -1)
                available[vertex_colouring[*neighbour]] = true;

        // Find the first available color
        vertex_colouring[*vit] = distance(available.begin(), std::find(available.begin(), available.end(), false));

        // Reset the values back to false for the next iteration
        for (tie(neighbour, neighbour_end) = adjacent_vertices(*vit, g); neighbour != neighbour_end; ++neighbour)
            if (vertex_colouring[*neighbour] != -1)
                available[vertex_colouring[*neighbour]] = false;
    }

    // print the result and find colour number
    for (vertex_descriptor v = 0; v < vertices_amount; ++v)
        std::cout << "Vertex " << v << " --->  Color " << vertex_colouring[v] << std::endl;

    return *std::max_element(vertex_colouring.begin(), vertex_colouring.end());
}

int main() { }
