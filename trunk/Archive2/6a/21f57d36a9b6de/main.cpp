#include <string>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/undirected_dfs.hpp>
#include <iostream>


std::vector<std::string> name = { "C0", "C1" };

//-----------------------------------------------------

struct detect_loops : public boost::dfs_visitor<>
{
//  template <typename Edge, typename Graph, typename Vertex>
  template <typename Edge, typename Graph>
  void back_edge(Edge e, const Graph& g) {
    std::cout << name[source(e, g)] << " -- " << name[target(e, g)] << "\n";
//    Vertex v1 = source(e, g);
  }
};


//-----------------------------------------------------
int main(int, char*[])
{
    typedef boost::adjacency_list<
		boost::vecS, boost::vecS,
		boost::undirectedS,
		boost::no_property,
		boost::property<
			boost::edge_color_t,
			boost::default_color_type
		>
	> graph_t;

  typedef boost::graph_traits<graph_t>::vertex_descriptor vertex_t;

  graph_t g(3);
  add_edge(0, 1, g);
  add_edge(0, 2, g);

  detect_loops vis;
  undirected_dfs(g, boost::root_vertex(vertex_t(0)).visitor(vis).edge_color_map(get(boost::edge_color, g)));

  return 0;
}
