#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <list>

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

struct Graph
{
    unordered_map<int, unordered_set<int> > nodeList;
    
    void addEdge(int i, int j);
    void sortNode(vector<int>& result, int node, unordered_set<int>& visited);
    vector<int> topoSort();
};

void
Graph::addEdge(int i, int j)
{
    nodeList[i].insert(j);
}


void 
Graph::sortNode(vector<int>& result, int node, unordered_set<int>& visited)
{
    cout << "Checking sortNode: " << node << std::endl;
    if(!visited.insert(node).second) return;
    cout << "Accepted sortNode: " << node << std::endl;
    if(nodeList.find(node) != nodeList.end())
    {
        const unordered_set<int>& neighbors = nodeList[node];
        for(auto it = neighbors.begin(); it != neighbors.end(); ++it)
        {
            sortNode(result, *it, visited);
        }
    }
    result.insert(result.begin(), node);
}

vector<int>
Graph::topoSort()
{
    vector<int> result;
    unordered_set<int> visited;
    for(auto it = nodeList.begin(); it != nodeList.end(); ++it)
    {
        cout << "node: " << it->first << ", neighbor size: " << it->second.size() << endl;
        sortNode(result, it->first, visited);
        cout << "nodeList size: " << nodeList.size() << endl;
    }
    return result;
}


int main()
{
    Graph g;
    g.addEdge(5,2);
    g.addEdge(5,0);
    g.addEdge(4,0);
    g.addEdge(4,1);
    g.addEdge(2,3);
    g.addEdge(3,1);
    
    std::cout << g.nodeList.size() << endl;
    
    vector<int> result = g.topoSort();
    std::cout << result.size() << std::endl;
    std::cout << " result is " << result << std::endl;
}
