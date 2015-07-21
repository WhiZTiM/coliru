#include <boost/graph/adjacency_list.hpp>
#include <iostream>

using namespace boost;

struct VertexProperties {
    int id;
    std::string label;
};

struct EdgeProperties {
    double weight;
};

using Graph_t = boost::adjacency_list<listS, listS, directedS, VertexProperties, EdgeProperties>;

//////////////////////////////////////////////////
// saving dotfiles for rendering to PNG
#include <boost/graph/graphviz.hpp>

template <typename G>
void save_dot_file(std::string const& fname, G& graph) {
    dynamic_properties dp;
    dp.property("node_id", boost::get(&VertexProperties::id,    graph));
    dp.property("label",   boost::get(&VertexProperties::label, graph));
    dp.property("weight",  boost::get(&EdgeProperties::weight,  graph));

    std::ofstream ofs(fname);
    write_graphviz_dp(ofs, graph, dp);
}

//////////////////////////////////////////////////
// Filtering graphs with a simple vertex filter
#include <boost/graph/filtered_graph.hpp>
#include <boost/function.hpp>

using V        = Graph_t::vertex_descriptor;
using Filtered = filtered_graph<Graph_t, keep_all, boost::function<bool(V)> >;

//////////////////////////////////////////////////
// Demo
int main()
{
    Graph_t g;

    // have a filtered "copy" f that just removes a set of vertices:
    std::set<V> removed_set;
    Filtered f(g, keep_all{}, [&](V v){ return removed_set.end() == removed_set.find(v); });

    // build a demo graph with 3 vertices
    auto u = boost::add_vertex(VertexProperties{ 10, "Ten"    }, g);
    auto v = boost::add_vertex(VertexProperties{ 20, "Twenty" }, g);
    auto w = boost::add_vertex(VertexProperties{ 30, "Thirty" }, g);

    /*auto e1 =*/ boost::add_edge(u, v, EdgeProperties { 0.5 }, g);
    /*auto e2 =*/ boost::add_edge(v, w, EdgeProperties { 1.5 }, g);
    /*auto e3 =*/ boost::add_edge(w, u, EdgeProperties { 2.5 }, g);

    ///////////////////////////////////////
    // save the original graph
    save_dot_file("original.dot", g);

    // empty filter:
    save_dot_file("filtered1.dot", f);

    // removing `v` ("Twenty")
    removed_set.insert(v);
    save_dot_file("filtered2.dot", f);
}

