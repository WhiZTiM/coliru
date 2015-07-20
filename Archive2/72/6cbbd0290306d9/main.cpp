// Example program
#include <iostream>
#include <map>
#include <list>

template <typename vtype = long long>
class Graph
{
    std::map<vtype, std::list<vtype>> adj_list ;

public:
    Graph() = default ;
    void insert(const vtype&, const std::list<vtype>&);
    std::size_t size() const ;
    
    template <typename T> friend std::ostream& operator<<(std::ostream&, const Graph<T>&);
};

template <typename vtype>
void Graph<vtype>::insert(const vtype& v, const std::list<vtype>& lt) {
    if(adj_list[v].size() == 0u)
        adj_list[v] = lt ;
    else
        adj_list[v].insert(adj_list[v].end(), lt.begin(), lt.end());
}

template <typename vtype>
std::size_t Graph<vtype>::size() const {
    return adj_list.size();
}

template <typename T>
std::ostream& operator<<(std::ostream& str, const Graph<T>& g)
{
    for(auto& k : g.adj_list) {
        str << k.first << " : [ ";
        for(auto e : k.second)
            str << e << " ";
        str << "]\n";
    }
    return str ;
}

int main() {
    Graph<> lob ;
    lob.insert(1, { 2, 3 }); // vertex 2 and 3 are adjacent to vertex 1
    lob.insert(1, { 4 });
    lob.insert(2, { 1, 3 });
    lob.insert(4, { 3, 5 });
    
    Graph<std::string> sob ;
    sob.insert("Vertex1", { "Vertex2", "Vertex3" });
    sob.insert("Vertex3", { "Vertex1" });
    
    std::cout << lob ;
    std::cout << sob ;
}