#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <tuple>
#include <iterator>
#include <type_traits>

template <typename vtype, 
          typename weight, 
          typename store_type> 
struct graph_storage
{
    using node_type = std::tuple<vtype, weight>;
    using vset_type = std::set<node_type>;
    
    typedef typename store_type::iterator iterator ;
    typedef typename store_type::const_iterator const_iterator ;
    typedef typename store_type::reverse_iterator reverse_iterator ;
    
    virtual vset_type adjacent(const vtype&) const;
    virtual std::size_t vertex_count() const;
    virtual std::size_t size() const { return data.size(); }
    
    virtual iterator begin() { return data.begin(); }
    virtual iterator end() { return data.end(); }
    virtual const_iterator cbegin() const { return data.cbegin(); }
    virtual const_iterator cend() const { return data.cend(); }
    
    graph_storage() = default ;
    graph_storage(const graph_storage&) = default ;
    graph_storage(graph_storage&&) = default ;
    virtual ~graph_storage() {}
    
protected:
    store_type data ;
}; 

template <typename vtype, 
          typename weight>
class adjacency_list : public graph_storage<vtype, weight, std::map<vtype, std::set<std::tuple<vtype, weight>>>>
{
public:
    typedef graph_storage<vtype, weight, std::map<vtype, std::set<std::tuple<vtype, weight>>>> base_type;
    typedef typename base_type::iterator iterator ;
    typedef typename base_type::const_iterator const_iterator;
    typedef typename base_type::reverse_iterator reverse_iterator;
    typedef typename base_type::node_type node_type ;
    typedef typename base_type::vset_type vset_type ;
    using list_type = std::map<vtype, vset_type> ;
    
    using base_type::adjacent ;
    using base_type::vertex_count ;
    
    // non-const methods
    adjacency_list() = default ;
    ~adjacency_list() { }
    void insert(const vtype&, const vset_type&);
    void insert(const vtype&, const std::initializer_list<vtype>&);
    
    // const methods
    std::vector<std::vector<bool>> adjacency_matrix() const ;
    std::size_t vertex_count() const override ;
    vset_type adjacent(const vtype&) const override;
    
    //friend functions
    template <typename T, typename W> friend 
    std::ostream& operator<<(std::ostream&, const adjacency_list<T, W>&);
    
protected:
    
    using base_type::data ;
    
};

template <typename vtype = unsigned long long, 
          typename weight = int, 
          typename store = adjacency_list<vtype, weight>>
class graph : public store
{
public:
    using store::adjacent ;
    using store::data ;
    
    graph() = default ;
    ~graph() {}
    
    bool path_exists(const vtype&, const vtype&) const ;
    std::set<vtype> path(const vtype&, const vtype&) const ;
    weight shortest_path(const vtype&, const vtype&, std::set<vtype>&) const ;
    
    template <typename T, typename W, typename S> friend 
    std::ostream& operator<<(std::ostream&, const graph<T, W, S>&);
};

template <typename vtype, typename weight>
void 
adjacency_list<vtype, weight>::insert(const vtype& v, const vset_type& lt) 
{
    data[v].insert(lt.begin(), lt.end());
}

template <typename vtype, typename weight>
void 
adjacency_list<vtype, weight>::insert(const vtype& v, const std::initializer_list<vtype>& lt) 
{
    for(auto& e : lt) 
        data[v].insert(std::tuple<vtype, weight>{ e, weight{} });
}

template <typename vtype, typename weight>
typename adjacency_list<vtype, weight>::vset_type 
adjacency_list<vtype, weight>::adjacent(const vtype& v) const 
{
    return data.at(v);
}

template <typename vtype, typename weight>
std::size_t
adjacency_list<vtype, weight>::vertex_count() const 
{
    std::set<vtype> vertices ;
    for(auto& pair : data)
        vertices.insert(pair.first);
    return vertices.size();
}

template <typename vtype, typename weight>
std::vector<std::vector<bool>> 
adjacency_list<vtype, weight>::adjacency_matrix() const 
{
    std::vector<std::vector<bool>> matrix ;
    char VERTEX_TYPE_HAS_TO_BE_UNSIGNED[std::is_unsigned<vtype>::value];
    auto row_size = vertex_count() ;
    
    for(auto& pair : data) 
    {
        matrix.emplace_back(row_size, false);
        for(auto& e : pair.second)
            matrix[matrix.size() - 1][std::get<0>(e)] = true ;
    }
    return matrix ;
}

template <typename vtype, typename weight, typename store>
bool 
graph<vtype, weight, store>::path_exists(const vtype& from, const vtype& to) const
{
    return path(from, to).size() > 0u ;
}

template <typename vtype, typename weight, typename store>
std::set<vtype>
graph<vtype, weight, store>::path(const vtype& from, const vtype& to) const 
{
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
            return path ;
        for(auto& v : adjacent(last_node))
            if(is_not_present(std::get<0>(v))) {
                std::set<vtype> new_path{path.begin(), path.end()};
                new_path.insert(std::get<0>(v));
                q.push(new_path);
            }
    }
    return std::set<vtype>{} ;
}

template <typename T, typename W>
std::ostream& operator<<(std::ostream& str, const adjacency_list<T, W>& g)
{
    for(auto& k : g.data) {
        str << k.first << " : [ ";
        for(auto e : k.second)
            str << std::get<0>(e) << " (" << std::get<1>(e) << ") ";
        str << "]\n";
    }
    return str ;
}

template <typename T, typename W, typename S>
std::ostream& operator<<(std::ostream& str, const graph<T, W, S>& g)
{
    str << (S&)g ;
    return str ;
}

int main() 
{
    graph<> lob ;
    lob.insert(1, { 2, 3 }); // vertex 2 and 3 are adjacent to vertex 1
    lob.insert(2, { 1, 3 });
    lob.insert(3, { 4 });
    lob.insert(4, { 3 });
    lob.insert(5, { });
    std::cout << lob ;
    
    auto path = lob.path(1, 4);
    std::cout << "Path from 1 -> 4 exists ? " << std::boolalpha << (path.size() > 0u) << ", then it is : [ " ;
    for(auto v : path)
        std::cout << v << " -> ";
    std::cout << "end ]" << std::endl ; 
    std::cout << "Path from 1 -> 5 exists ? " << lob.path_exists(1, 5); 
    
    auto adj_mat = lob.adjacency_matrix();
    for(const auto& row : adj_mat)
    {
        std::cout << std::endl ;
        for(const auto& e : row)
            std::cout << e << " " ;
    }
}