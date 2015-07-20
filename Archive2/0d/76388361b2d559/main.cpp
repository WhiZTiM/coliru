#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

template <typename vtype = long long>
class Graph
{
    std::map<vtype, std::set<vtype>> adj_list ;

public:
    Graph() = default ;
    void insert(const vtype&, const std::set<vtype>&);
    std::size_t size() const ;
    bool path_exists(const vtype&, const vtype&);
    
    template <typename T> friend std::ostream& operator<<(std::ostream&, const Graph<T>&);
};

template <typename vtype>
void Graph<vtype>::insert(const vtype& v, const std::set<vtype>& lt) {
    if(adj_list[v].size() == 0u)
        adj_list[v] = lt ;
    else
        adj_list[v].insert(lt.begin(), lt.end());
}

template <typename vtype>
std::size_t Graph<vtype>::size() const {
    return adj_list.size();
}

template <typename vtype>
bool Graph<vtype>::path_exists(const vtype& from, const vtype& to) {
    std::set<vtype> path ;
    path.insert(from);
    std::queue<std::set<vtype>> q ;
    q.push(path);
    
    auto is_not_present = [&path](const vtype& v) {
        return (std::find(path.begin(), path.end(), v) == path.end());
    };
    
    auto get_last_node = [&path]() {
        auto it = path.cend();
        --it ;
        return *it ;
    } ;
    
    while(!q.empty()) {
        path = q.front() ;
        q.pop();
        auto last_node = get_last_node();
        if(last_node == to)
            return true ;
        for(auto& v : adj_list[last_node])
            if(is_not_present(v)) {
                std::set<vtype> new_path{path.begin(), path.end()};
                new_path.insert(v);
                q.push(new_path);
            }
    }
    return false ;
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
    lob.insert(2, { 1, 3 });
    lob.insert(3, { 4 });
    lob.insert(4, { 3 });
    lob.insert(5, { });
    
    Graph<std::string> sob ;
    sob.insert("Vertex1", { "Vertex2", "Vertex3" });
    sob.insert("Vertex3", { "Vertex1" });
    
    std::cout << lob ;
    std::cout << sob ;
    std::cout << std::boolalpha << lob.path_exists(1, 4) << "\n"; 
    std::cout << lob.path_exists(1, 5); 
}