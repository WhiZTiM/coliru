#include <deque>
#include <queue>
#include <iostream>
#include <functional>
#include <vector>

struct TreeNode
{
    /* @brief Constructor
       @param name_     Label of node
       @parem node_no_  State of node
       @param dist_     Distance of node from start
    */
    TreeNode(char name_, int node_no_ = 0, int dist_ = 0, int estimated_dist_ = 0);
    /* @brief Function to expand the node and access the children nodes.
       @return Vector of TreeNodes that are the children.
    */
    std::vector<TreeNode> Expand();

    //Information about the node (should probably be private but this adds extra work)
    char name;
    //This also represents the state of that node in the tree (again probably not the best thing)
    int node_no;
    //Distance from start
    int dist;
    //Estimated straight line distance to the goal.
    int estimated_dist;
};

TreeNode::TreeNode(char name_, int node_no_, int dist_, int estimated_dist_)
    : name(name_), node_no(node_no_), dist(dist_), estimated_dist(estimated_dist_)
{
}

std::vector<TreeNode> TreeNode::Expand()
{
    std::vector<TreeNode> children;
    switch (node_no)
    {
        case 0:
            children.emplace_back('A', 1, 2, 8);
            children.emplace_back('B', 2, 3, 9);
            break;
        case 1:
            children.emplace_back('B', 3, dist + 2, 9);
            children.emplace_back('D', 4, dist + 4, 5);
            break;
        case 2:
            children.emplace_back('A', 5, dist + 2, 8);
            children.emplace_back('C', 6, dist + 5, 10);
            children.emplace_back('D', 7, dist + 7, 5);
            break;
        case 3:
            children.emplace_back('C', 8, dist + 5, 10);
            children.emplace_back('D', 9, dist + 7, 5);
            break;
        case 4:
            children.emplace_back('B', 10, dist + 7, 9);
            children.emplace_back('G', 11, dist + 6, 0);
            break;
        case 5:
            children.emplace_back('D', 12, dist + 4, 5);
            break;
        case 7:
            children.emplace_back('A', 13, dist + 4, 8);
            children.emplace_back('G', 14, dist + 6, 0);
            break;
        case 9:
            children.emplace_back('G', 15, dist + 6, 0);
            break;
        case 10:
            children.emplace_back('C', 16, dist + 5, 10);
        case 12:
            children.emplace_back('G', 17, dist + 6, 0);
            break;
        default:
            children.clear();
    }
    return children;
}

enum class SearchType
{
    BreadthFirst, DepthFirst, UniformCost, AStar
};

//Implementing Breadth-First and Depth-First searches as per textbook
//This searches do not check for repeated states as they use a TreeNode class
//that does not have repeated states. If this was a graph search, repeated
//states would need to be checked.
void CostlessSearch(char initial_state, char goal_state, SearchType type)
{
    if (initial_state == goal_state)
    {
        std::cout << "Initial is goal.\n";
        return;
    }

    TreeNode node(initial_state);
    std::deque<TreeNode> frontier;

    //Different actions are required for different search types
    if (type == SearchType::BreadthFirst)
    {
        frontier.push_back(std::move(node)); //Breadth-First is FIFO
    }
    else
    {
        frontier.push_front(std::move(node)); //Depth-First is LIFO
    }

    while(!frontier.empty())
    {
        TreeNode node = std::move(frontier.front());
        frontier.pop_front();

        std::cout << "About to expand: " << node.node_no << std::endl;
        auto children = node.Expand();

        for (auto &child_node : children)
        {
            bool in_frontier = false;
            for (auto &node : frontier)
            {
                if (node.node_no == child_node.node_no)
                {
                    in_frontier = true;
                }
            }

            if (!in_frontier)
            {
                if (child_node.name == goal_state)
                {
                    //Goal checked here to avoid expanding nodes unnecessarily
                    std::cout << "Found goal, node: " << child_node.node_no << ".\n";
                    return;
                }
                std::cout << "Adding " << child_node.node_no << " to frontier.\n";
                if (type == SearchType::BreadthFirst)
                {
                    frontier.push_back(std::move(child_node));
                }
                else
                {
                    frontier.push_front(std::move(child_node));
                }
            }
        }
    }
    std::cout << "Frontier is empty. Exiting...\n";
}

void CostSearch(char initial_state, char goal_state, SearchType type)
{
    if (initial_state == goal_state)
    {
        std::cout << "Initial is goal.\n";
        return;
    }

    TreeNode node(initial_state);

    std::function<bool(TreeNode, TreeNode)> comp_func;

    if (type == SearchType::AStar)
    {
        comp_func = [](TreeNode lhs, TreeNode rhs)
        {
            if ((lhs.dist + lhs.estimated_dist) == (rhs.dist + rhs.estimated_dist))
            {
                return (lhs.name > rhs.name);
            }
            else
            {
                return ((lhs.dist + lhs.estimated_dist) > (rhs.dist + rhs.estimated_dist));
            }
        };
    }
    else
    {
        comp_func = [](TreeNode lhs, TreeNode rhs)
        {
            if (lhs.dist == rhs.dist)
            {
                return (lhs.name > rhs.name);
            }
            else
            {
                return (lhs.dist > rhs.dist);
            }
        };
    }

    typedef std::priority_queue<TreeNode, std::vector<TreeNode>, decltype(comp_func)> pri_queue;
    pri_queue frontier(comp_func);

    frontier.push(std::move(node));

    while(!frontier.empty())
    {
        TreeNode node = std::move(frontier.top());
        frontier.pop();

        if (node.name == goal_state)
        {
            //Goal checked here to avoid accepting sub-optimal goals.
            std::cout << "Found goal, node: " << node.node_no << ".\n";
            return;
        }

        std::cout << "About to expand: " << node.node_no << " with a distance of: ";
        if (type == SearchType::AStar)
        {
            std::cout << node.dist + node.estimated_dist << std::endl;
        }
        else
        {
            std::cout << node.dist << std::endl;
        }
        
        auto children = node.Expand();

        for (auto &child_node : children)
        {
            bool in_frontier = false;
            TreeNode temp = std::move(frontier.top());
            for (std::size_t i = 0; i < frontier.size(); i++)
            {
                //priority queue can not be iterated over so we must "iterate" like this
                frontier.pop();
                if (temp.node_no == child_node.node_no)
                {
                    in_frontier = true;
                    break;
                }
                frontier.push(std::move(temp));
                temp = std::move(frontier.top());
            }

            if (!in_frontier)
            {
                std::cout << "Adding " << child_node.node_no << " to frontier.\n";
                frontier.push(std::move(child_node));
            }
            else
            {
                if (comp_func(child_node, temp))
                {
                    frontier.push(std::move(child_node));
                }
                else
                {
                    frontier.push(std::move(temp));
                }
            }
        }
    }
    std::cout << "Frontier is empty. Exiting...\n";
}

int main(int argv, char ** argc)
{
    std::cout << "Breadth first search:\n";
    CostlessSearch('S', 'G', SearchType::BreadthFirst);
    std::cout << "\nDepth first search:\n";
    CostlessSearch('S', 'G', SearchType::DepthFirst);
    std::cout << "\nUniform cost search:\n";
    CostSearch('S', 'G', SearchType::UniformCost);
    std::cout << "\nA* search:\n";
    CostSearch('S', 'G', SearchType::AStar);

    return 0;
}
