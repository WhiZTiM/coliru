#include <boost/graph/adjacency_list.hpp>
#include <iostream>
#include <unordered_set>

struct VertexProperties {
    int id;
    int label;
    VertexProperties(unsigned i = 0, unsigned l = 0) : id(i), label(l) {}
};

struct EdgeProperties {
    unsigned id;
    unsigned label;
    EdgeProperties(unsigned i = 0, unsigned l = 0) : id(i), label(l) {}
};

namespace boost {
template <> struct hash<VertexProperties> {
    size_t operator()(VertexProperties const &v) const {
        auto seed = hash_value(v.id);
        hash_combine(seed, v.label);
        return seed;
    }
};
template <> struct hash<EdgeProperties> {
    size_t operator()(EdgeProperties const &e) const {
        auto seed = hash_value(e.id);
        hash_combine(seed, e.label);
        return seed;
    }
};
}

struct GraphProperties {
    unsigned id;
    unsigned label;
    GraphProperties(unsigned i = 0, unsigned l = 0) : id(i), label(l) {}
};

// adjacency_list
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperties, EdgeProperties, GraphProperties> Graph;
typedef boost::graph_traits<Graph>::edge_descriptor edge_descriptor;

struct hashedge {
    hashedge(Graph const &g) : _g(g) {}

    size_t operator()(const edge_descriptor e) const {
        using namespace boost;

        size_t seed = 42;
        hash_combine(seed, _g[source(e, _g)]);
        hash_combine(seed, _g[e].label);
        hash_combine(seed, _g[target(e, _g)]);
        return seed;
    }

    private:
    Graph const &_g;
};

int main() {
    std::vector<Graph> dataG;
    for (auto& g : dataG) {
        auto es = edges(g);
        std::unordered_set<edge_descriptor, hashedge> edgehash(es.first, es.second, 0ul, hashedge(g));
    }
}
