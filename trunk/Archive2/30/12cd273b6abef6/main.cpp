#include "tree_node.hpp"

namespace lab_one
{
    TreeNode::TreeNode(char name_, int node_no_, int dist_)
	    : name(name_), node_no(node_no_), dist(dist_)
	{
	}

	bool TreeNode::operator <(const TreeNode& rhs) const
	{
	    if (this->dist > rhs.dist) //Dirty hack to make queue reversed
	    {
	        return true;
	    }
	    else if (this->dist == rhs.dist)
	    {
	        return (this->name > rhs.name); //If distances are equal
	                                        //we need to go alphabetically
	    }
	    else
	    {
	        return false;
	    }
	}

	std::vector<TreeNode> TreeNode::Expand()
	{
	    sd::vector<TreeNode> children;
	    switch (node_no)
	    {
	        case 0:
	            children.emplace_back('A', 1, 2);
	            children.emplace_back('B', 2, 3);
	            break;
	        case 1:
	            children.emplace_back('B', 3, dist + 2);
	            children.emplace_back('D', 4, dist + 4);
	            break;
	        case 2:
	            children.emplace_back('A', 5, dist + 2);
	            children.emplace_back('C', 6, dist + 5);
	            children.emplace_back('D', 7, dist + 7);
	            break;
	        case 3:
	            children.emplace_back('C', 8, dist + 5);
	            children.emplace_back('D', 9, dist + 7);
	            break;
	        case 4:
	            children.emplace_back('B', 10, dist + 7);
	            children.emplace_back('G', 11, dist + 6);
	            break;
	        case 5:
	            children.emplace_back('D', 12, dist + 4);
	            break;
	        case 7:
	            children.emplace_back('A', 13, dist + 4);
	            children.emplace_back('G', 14, dist + 6);
	            break;
	        case 9:
	            children.emplace_back('G', 15, dist + 6);
	            break;
	        case 10:
	            children.emplace_back('C', 16, dist + 5);
	        case 12:
	            children.emplace_back('G', 17, dist + 6);
	            break;
	        default:
	            children.clear();
	    }
	    return children;
	}	
}
