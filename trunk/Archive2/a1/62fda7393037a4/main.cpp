#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/function_output_iterator.hpp>

typedef boost::adjacency_list<
    boost::setS, // outedge list
	boost::setS, // vertex list
	boost::directedS, // undirected 
	boost::property<boost::vertex_index_t, int>, // vertex prop
	boost::no_property, // edge prop
	boost::no_property, // graph prop
	boost::setS // edgelist
> Graph;

bool hasCycle(const Graph& aG)
{
	try {
		boost::topological_sort(
			aG,
			boost::make_function_output_iterator([](Graph::vertex_descriptor){})
		);
	}
	catch (boost::not_a_dag const&)
	{
		return true;
	}
	return false;
}

#include <boost/graph/random.hpp>
#include <random>

int main() {
	std::mt19937 prng{ std::random_device{}() };
	Graph g;
	boost::generate_random_graph(g, 100, 200, prng);
	auto index = boost::get(boost::vertex_index, g);

	int gen_id = 0;
	for (auto vd : boost::make_iterator_range(boost::vertices(g)))
		boost::put(index, vd, gen_id++);

	bool check = hasCycle(g);
    return check? 1 : 2;
}
