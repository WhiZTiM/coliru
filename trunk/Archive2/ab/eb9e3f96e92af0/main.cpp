#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/function_output_iterator.hpp>

typedef boost::adjacency_list<
    boost::setS, // outedge list
    boost::vecS, // vertex list
    boost::directedS, // undirected 
    boost::no_property, // vertex prop
    boost::no_property, // edge prop
    boost::no_property, // graph prop
    boost::setS // edgelist
    > Graph;


bool hasCycle(const Graph& aG) 
{
    try {
        boost::topological_sort(
            aG, 
            boost::make_function_output_iterator([](int){}));
    } catch(boost::not_a_dag const&)
    {
        return true;
    }
    return false;
} 

int main() {
    return 0;
}