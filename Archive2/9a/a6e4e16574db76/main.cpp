#include <memory>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/fruchterman_reingold.hpp>
#include <boost/graph/random_layout.hpp>
#include "/Archive2/45/a4410ef1bd3024/main.cpp" // alias <libs/graph/src/read_graphviz_new.cpp>
#include <boost/graph/topology.hpp>
#include <boost/random.hpp>

using namespace boost;

struct Vertex {
    std::string name;
};

    struct AttractionF {
        template <typename EdgeDescriptor, typename Graph>
            double operator()(EdgeDescriptor /*ed*/, double k, double d, Graph const& /*g*/) const {
                //std::cout << "DEBUG af('" << g[source(ed, g)].name << " -> " << g[target(ed, g)].name << "; k:" << k << "; d:" << d << ")\n";
                return (d*d/k);
            }
    };

using Graph = adjacency_list<vecS, vecS, undirectedS, Vertex>;

Graph make_sample();

int main() {
    auto g = make_sample();

    using Topology = square_topology<boost::mt19937>;
    using Position = Topology::point_type;

    std::vector<Position> positions(num_vertices(g));
    square_topology<boost::mt19937> topology;

    random_graph_layout(g, 
                make_iterator_property_map(positions.begin(), boost::identity_property_map{}),
                topology);

    fruchterman_reingold_force_directed_layout(
                g,
                make_iterator_property_map(positions.begin(), boost::identity_property_map{}),
                topology,
                attractive_force(AttractionF())
            );

    dynamic_properties dp;
    dp.property("node_id", get(&Vertex::name, g));
    write_graphviz_dp(std::cout, g, dp);
}

Graph make_sample() {
    std::string const sample_dot = R"(
        graph {
            "0"        -- "5";
            "Kevin"    -- "Martin";
            "Ryan"     -- "Leo";
            "Y"        -- "S";
            "Kevin"    -- "S";
            "American" -- "USA";
        }
    )";
    Graph g;

    dynamic_properties dp;
    dp.property("node_id", get(&Vertex::name, g));

    read_graphviz(sample_dot, g, dp);

    return g;
}
