#include <boost/graph/graphviz.hpp>
#include "/Archive2/45/a4410ef1bd3024/main.cpp" // alias <libs/graph/src/read_graphviz_new.cpp>
#include <iostream>

struct DotVertex {
    std::string name;
    std::string label;
    int peripheries;
    std::string style;
    int width;
};

struct DotEdge {
    std::string label;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
        DotVertex, DotEdge> graph_t;

int main() {
    graph_t graphviz;
    boost::dynamic_properties dp(boost::ignore_other_properties);

    dp.property("node_id",     boost::get(&DotVertex::name,        graphviz));
    dp.property("label",       boost::get(&DotVertex::label,       graphviz));
    dp.property("peripheries", boost::get(&DotVertex::peripheries, graphviz));
    dp.property("label",       boost::get(&DotEdge::label,         graphviz));

    bool status = boost::read_graphviz(std::cin, graphviz, dp);
    return status? 0 : 255;
}
