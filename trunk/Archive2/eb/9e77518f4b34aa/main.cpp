#include <boost/graph/graphviz.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <iostream>
#include <iomanip>

using namespace boost;

std::string prettyprint(std::array<double, 2> const& arr) {
    std::ostringstream oss;
    oss << "{" << arr[0] << "," << arr[1] << "}";
    return oss.str();
}

int main()
{
    using namespace boost;
    typedef adjacency_list<vecS, vecS, directedS, no_property, std::array<double, 2>> Graph;
    Graph g;
    auto e = add_edge(0, 1, {123,456}, g);
    std::cout << g[e.first];

    dynamic_properties dp;
    dp.property("node_id", get(vertex_index, g));
    dp.property("label",  make_transform_value_property_map(&prettyprint, get(edge_bundle, g)));
    write_graphviz_dp(std::cout, g, dp);
}
