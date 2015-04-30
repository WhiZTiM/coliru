#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

using namespace boost;

std::string prettyprint(std::array<double, 2> const& arr) {
    std::ostringstream oss;
    oss << "{" << arr[0] << "," << arr[1] << "}";
    return oss.str();
}

int main()
{
    using namespace boost;
    typedef adjacency_list<vecS, vecS, directedS, no_property, std::array<double,2>> Graph;
    Graph g;
    add_edge(0, 1, {123,456}, g);
    write_graphviz(std::cout, g, default_writer(),
            make_label_writer(make_transform_value_property_map(&prettyprint, get(edge_bundle, g))));
}
