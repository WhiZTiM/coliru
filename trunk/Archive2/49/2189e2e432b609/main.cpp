#include <iostream>
#include <vector>

#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_utility.hpp>

// Create a struct to hold properties for each vertex
struct VertexProperties { 
    int p1; 
};

// Create a struct to hold properties for each edge
struct EdgeProperties { 
    int p1; 
};

// Define the type of the graph
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperties, EdgeProperties> Graph;

int main() {
    // Create a graph object
    Graph g;

    // Add vertices
    Graph::vertex_descriptor 
        v0 = boost::add_vertex(g),
        v1 = boost::add_vertex(g),
        v2 = boost::add_vertex(g);

    g[v0].p1 = 1;
    g[v1].p1 = 2;
    g[v2].p1 = 3;

    // Add edges
    Graph::edge_descriptor e0 = boost::add_edge(v0, v1, g).first;
    Graph::edge_descriptor e1 = boost::add_edge(v1, v2, g).first;

    g[e0].p1 = 1;
    g[e1].p1 = 2;

    boost::print_graph(g, boost::get(&VertexProperties::p1, g));

    // set up a weight map:
    boost::property_map<Graph, int EdgeProperties::*>::type weights = boost::get(&EdgeProperties::p1, g);

    // you can pass it to dijkstra using direct or named params. Let's do the simplest
    boost::dijkstra_shortest_paths(g, v0, boost::no_named_parameters() .weight_map(weights));
}
