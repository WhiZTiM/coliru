#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/function_output_iterator.hpp>

typedef boost::adjacency_list<
    boost::setS, // outedge list
	boost::setS, // vertex list
	boost::directedS, // undirected 
	boost::no_property, // vertex prop
	boost::no_property, // edge prop
	boost::no_property, // graph prop
	boost::setS // edgelist
> Graph;

bool hasCycle(const Graph& aG)
{
	try {
		std::map<Graph::vertex_descriptor, size_t> index;
		auto pmap = boost::make_assoc_property_map(index);
		
		for (auto vd : boost::make_iterator_range(boost::vertices(aG)))
			index[vd] = index.size();

		boost::topological_sort(
			aG,
			boost::make_function_output_iterator([](Graph::vertex_descriptor){}),
			boost::vertex_index_map(pmap));
	}
	catch (boost::not_a_dag const&)
	{
		return true;
	}
	return false;
}

int main() {
}
