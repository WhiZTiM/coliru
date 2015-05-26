#include <string>
#include <istream>
#include <sstream>

template <typename Graph>
bool read_coloring_problem(std::istream& dimacs, Graph& g) {
    size_t vertices = 0, edges = 0;

    std::string line;
    while (getline(dimacs, line))
    {
        std::istringstream iss(line);
        char ch;
        if (iss >> ch)
        {
            size_t from, to;
            std::string format;

            switch(ch) {
                case 'c': break;
                case 'p': 
                    if (vertices||edges) return false;
                    if (iss >> format >> vertices >> edges) {
                        if ("edge" != format) return false;
                    }
                    break;
                case 'e': 
                    if (edges-- && (iss >> from >> to) && (add_edge(from-1, to-1, g).second))
                        break;
                default: 
                    return false;
            }
        }
    }

    return !(edges || !dimacs.eof());
}

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <fstream>
#include <iostream>

using namespace boost::graph;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;

int main() {
    Graph g2;
    std::ifstream input("myciel4.col");
    if (read_coloring_problem(input, g2))
    {
        std::cout << "Nodes: " << num_vertices(g2) << "\n";
        std::cout << "Edges: " << num_edges(g2)    << "\n";
        boost::write_graphviz(std::cout, g2);
    } else {
        std::cout << "Parse error\n";
    }
}
