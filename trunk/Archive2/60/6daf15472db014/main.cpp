#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <iostream>
using namespace boost;

inline char const* color_to_string(default_color_type c) {
    switch(c) {
        case default_color_type::red_color:   return "red";
        case default_color_type::green_color: return "green";
        case default_color_type::gray_color:  return "gray";
        case default_color_type::white_color: return "white";
        case default_color_type::black_color: return "black";
    }
    return ""; // not known
}


int main() {
    typedef property<edge_name_t, std::string> EdgeProperties;
    typedef property<vertex_name_t, std::string, property<vertex_color_t, default_color_type>> VertexProperties;
    typedef adjacency_list<vecS, vecS, directedS, VertexProperties, EdgeProperties> Graph;
    typedef graph_traits<Graph>::vertex_descriptor Vertex;
    typedef graph_traits<Graph>::edge_descriptor Edge;

    Graph g;
    property_map<Graph, vertex_name_t>::type vertex_label = get(vertex_name, g);
    property_map<Graph, vertex_color_t>::type color_map = get(vertex_color, g);
    property_map<Graph, edge_name_t>::type edge_label = get(edge_name, g);

    Vertex v1 = add_vertex(g);
    vertex_label[v1] = "v1";

    put(color_map, v1, boost::red_color);

    dynamic_properties dp;
    dp.property("node_id", get(vertex_index, g));
    dp.property("label", vertex_label);
    dp.property("label", edge_label);
    dp.property("color", make_transform_value_property_map(&color_to_string, color_map));

    write_graphviz_dp(std::cout, g, dp);
}
