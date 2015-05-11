#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <stdexcept>

struct Node
{
    std::unordered_set<char> out;
    std::unordered_set<char> in;
};

std::unordered_map<char, Node> graph;

void edge (char from, char to)
{
    graph[from].out.insert(to);
    graph[to].in.insert(from);
}

std::vector<char> sort ()
{
    std::vector<char> result;
    result.reserve(graph.size());
    
    for (const auto& node : graph)
    {
        if (node.second.in.empty())
        {
            result.push_back(node.first);
        }
    }
    
    size_t offset = 0;
    while (result.size() < graph.size())
    {
        size_t start = offset;
        offset = result.size();
        for (size_t i = start; i < offset; i++)
        {
            auto& out = graph[result[i]].out;
            for (char outgoing : out)
            {
                auto& in = graph[outgoing].in;
                in.erase(result[i]);
                if (in.empty())
                {
                    result.push_back(outgoing);
                }
            }
            //out.clear();
        }
        if (offset == result.size())
            throw std::invalid_argument("the graph contains a loop");
    }
    
    return result;
}   

int main ()
{
    edge ('F', 'R');
    edge ('N', 'R');
    edge ('R', 'T');
    edge ('X', 'R');
    edge ('X', 'N');
    //edge ('T', 'X');

    for (auto n : sort ())
    {
        std::cout << n;
    }
    std::cout << '\n';
}