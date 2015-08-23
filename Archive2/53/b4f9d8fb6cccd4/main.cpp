#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

using namespace std;

struct GraphNode
{
    int label;
    vector<GraphNode*> neighbors;
    GraphNode(int label_) : label(label_) {}
};


class Graph
{
private:
    unordered_map<int, unordered_set<int> > nodes;
public:
    void addEdge(int i, int j)
    {
        nodes[i].insert(j);
    }
    
    bool detectCycle(int node, unordered_set<int>& visited, unordered_set<int>& intPath);
    bool detectGraphCycle();
};

bool Graph::detectCycle(int node, unordered_set<int>& visited, unordered_set<int>& inPath)
{
    if(!inPath.insert(node).second)
    {
        return true;
    }
    
    if(!visited.insert(node).second)
    {
        return false;
    }
    
    unordered_set<int>& neighbors = nodes[node];
    for(auto it = neighbors.begin(); it != neighbors.end(); ++it)
    {
        if(detectCycle(*it, visited, inPath))
        {
            return true;
        }
    }
    
    inPath.erase(node);
    return false;
}

bool Graph::detectGraphCycle()
{
    unordered_set<int> visited;
    unordered_set<int> inPath;
    for(auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        if(detectCycle(it->first, visited, inPath))
        {
            return true;
        }
    }
    return false;
}


int main()
{
    Graph g;
    g.addEdge(0,1);
    g.addEdge(0,2);
//    g.addEdge(1,2);
//    g.addEdge(2,0);
    g.addEdge(2,3);
    g.addEdge(3,0);
    
    bool result = g.detectGraphCycle();
    std::cout << " result is " << result << std::endl;
}
